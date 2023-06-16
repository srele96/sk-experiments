const { get_elements } = require('./index');

describe('elements', () => {
  test('should return correct array of elements', () => {
    const length = 7;
    const main_element = 4;
    const elements = get_elements({ length })(main_element);

    expect(elements).toEqual([
      { order: -3 },
      { order: -2 },
      { order: -1 },
      { order: 0 },
      { order: 1 },
      { order: 2 },
      { order: 3 },
    ]);
  });

  test(
    'should return correct array of elements ' + 'when first is main element',
    () => {
      const length = 7;
      const main_element = 1;
      const elements = get_elements({ length })(main_element);

      expect(elements).toEqual([
        { order: 0 },
        { order: 1 },
        { order: 2 },
        { order: 3 },
        { order: 4 },
        { order: 5 },
        { order: 6 },
      ]);
    }
  );

  test(
    'should return correct array of elements ' + 'when last is main element',
    () => {
      const length = 7;
      const main_element = 7;
      const elements = get_elements({ length })(main_element);

      expect(elements).toEqual([
        { order: -6 },
        { order: -5 },
        { order: -4 },
        { order: -3 },
        { order: -2 },
        { order: -1 },
        { order: 0 },
      ]);
    }
  );

  test(
    'should return correct array of elements ' +
      'when arbitary is main element',
    () => {
      const length = 7;
      const main_element = 6;
      const elements = get_elements({ length })(main_element);

      expect(elements).toEqual([
        { order: -5 },
        { order: -4 },
        { order: -3 },
        { order: -2 },
        { order: -1 },
        { order: 0 },
        { order: 1 },
      ]);
    }
  );

  test('should throw when options are missing', () => {
    expect(() => get_elements()).toThrow('options are required');
  });

  test('should throw when length is invalid', () => {
    function get_error_message(value) {
      return 'length must be a number, received ' + typeof value;
    }

    const length = {
      object: {},
      nan: NaN,
      array: [],
      boolean: true,
      null: null,
      string: 'string',
    };

    Object.values(length).forEach((value) => {
      expect(() => get_elements({ length: value })).toThrow(
        get_error_message(value)
      );
    });
  });

  test('should throw when main element is missing', () => {
    const length = 3;

    expect(() => get_elements({ length })()).toThrow(
      'main_element must be a number, received undefined'
    );
  });

  test('should throw when main element is out of range', () => {
    const length = 3;
    const out_of_range = 4;

    expect(() => get_elements({ length })(out_of_range)).toThrow(
      'main_element out of range'
    );
  });

  test('should modify elements with callback correctly', () => {
    const length = 7;
    const main_element = 4;
    const elements = get_elements({
      length,
      callback: (element) => {
        return {
          ...element,
          multiplied: element.order * 5,
        };
      },
    })(main_element);

    expect(elements).toEqual([
      { order: -3, multiplied: -15 },
      { order: -2, multiplied: -10 },
      { order: -1, multiplied: -5 },
      { order: 0, multiplied: 0 },
      { order: 1, multiplied: 5 },
      { order: 2, multiplied: 10 },
      { order: 3, multiplied: 15 },
    ]);
  });
});
