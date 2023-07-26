function generateElements(option) {
  if (!option) {
    throw new Error('option is required');
  }

  function assertDataValuesAreSameLength() {
    if (!option.data) {
      throw new Error('option.data is required');
    }

    const dataKeys = Object.keys(option.data);
    if (dataKeys.length > 0) {
      let lengths = new Set();
      for (const value of Object.values(option.data)) {
        if (!Array.isArray(value)) {
          throw new Error(
            'All option.data values must be arrays, received ' + typeof value
          );
        }
        lengths.add(value.length);
        if (lengths.size > 1) {
          throw new Error('All option.data arrays must be of the same length');
        }
      }
    } else {
      throw new Error('option.data must have at least one key');
    }
  }

  assertDataValuesAreSameLength();

  let acc = {};

  function insertDataProperties() {
    for (const key in option.data) {
      const value = option.data[key];
      for (let i = 0; i < value.length; ++i) {
        if (!acc[i]) {
          acc[i] = {};
        }
        acc[i][key] = value[i];
      }
    }
  }

  insertDataProperties();

  if (typeof option.each === 'function') {
    function modifyEachElement() {
      acc = Object.entries(acc).reduce((accumulated, [key, value]) => {
        const result = option.each(key, value);

        if (!result) {
          throw new Error(
            'option.each callback must return an object with key and value properties'
          );
        }

        if (!result.key) {
          throw new Error(
            'option.each callback must return an object with a key property'
          );
        }

        accumulated[result.key] = result.value;
        return accumulated;
      }, {});
    }

    modifyEachElement();
  }

  // Bad idea to silently ignore received invalid key because a user has to
  // waste lots of time figuring out whether he or the library is wrong.
  //
  // Alert user of invalid behavior.
  const validModifyOptions =
    option.modify &&
    option.modify.keyA &&
    option.modify.keyB &&
    acc[option.modify.keyA] &&
    acc[option.modify.keyB] &&
    typeof option.modify.cb === 'function';

  if (validModifyOptions) {
    const { keyA, keyB, cb } = option.modify;
    const result = cb(acc[keyA], acc[keyB]);
    acc[keyA] = result[keyA];
    acc[keyB] = result[keyB];
  }

  return acc;
}

module.exports.generateElements = generateElements;
