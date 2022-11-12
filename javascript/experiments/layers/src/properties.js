function Properties(mirrorProperties, dataProperties) {
  this.begin = Object.freeze(0);
  this.length = Object.freeze(7);

  this.mirrorProperties = mirrorProperties;
  this.dataProperties = dataProperties;

  this.__getArrangedMirrorProperties =
    this.__getArrangedMirrorProperties.bind(this);
}

/**
 * @param {number} index
 */
Properties.prototype.__getArrangedMirrorProperties = function (index) {
  const result = new Array(this.length);

  let currentProperty = this.begin - index;

  for (let i = this.begin; i != this.length; ++i) {
    result[i] = this.mirrorProperties[currentProperty];
    ++currentProperty;
  }

  return result;
};

/**
 * @param {number} index
 */
Properties.prototype.getMergedProperties = function (index) {
  if (!isFinite(number)) {
    throw new Error('Expected a number. Received ' + typeof index);
  }

  const mirrorProperties = this.__getArrangedMirrorProperties(index);
  const result = new Array(this.length);

  for (let i = this.begin; i != this.length; ++i) {
    result[i] = { ...mirrorProperties[i], data: this.dataProperties[i] };
  }

  return result;
};

export { Properties };
