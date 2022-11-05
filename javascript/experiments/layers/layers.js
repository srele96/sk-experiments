'use strict';

const invariant = Object.freeze({
  validOptions: Object.freeze(function (options, validOptions) {
    const hasValidOptions =
      options &&
      Object.keys(options).length === validOptions.length &&
      Object.keys(options).every((option) => validOptions.includes(option));

    if (!hasValidOptions) {
      throw new Error(
        'received invalid options, valid options are: ' +
          validOptions.join(', ')
      );
    }
  }),
  validNumbers: Object.freeze(function (...numbers) {
    if (!numbers.every((number) => Number.isFinite(number))) {
      throw new Error('received invalid numbers');
    }
  }),
  validArray: Object.freeze(function (array) {
    if (!Array.isArray(array)) {
      throw new Error('received unexpected type, expected array');
    }
  }),
  lengthEqualOrLess: Object.freeze(function (array, length) {
    if (array.length > length) {
      throw new Error(
        'expected an array to have equal or smaller length than ' + length
      );
    }
  }),
});

function Calculate(options) {
  invariant.validOptions(options, ['offset', 'initialOffset']);
  invariant.validNumbers(options.offset, options.initialOffset);

  this.__offset = options.offset;
  this.__initialOffset = options.initialOffset;
}

Calculate.prototype.__sizeToTwoEdges = function ({ topLayerSize, size }) {
  return topLayerSize - size;
};

Calculate.prototype.__sizeToOneEdge = function ({ topLayerSize, size }) {
  return this.__sizeToTwoEdges({ topLayerSize, size }) / 2;
};

Calculate.prototype.__sizeToShowOffset = function ({ order }) {
  return order * this.__offset + this.__initialOffset;
};

Calculate.prototype.__sizeToMove = function ({ topLayerSize, size, order }) {
  return (
    this.__sizeToOneEdge({ topLayerSize, size }) +
    this.__sizeToShowOffset({ order })
  );
};

Calculate.prototype.topLayerOffset = function ({ topLayerIndex }) {
  invariant.validNumbers(topLayerIndex);

  return topLayerIndex * this.__offset + this.__initialOffset;
};

Calculate.prototype.sizeToMoveInDirection = function ({
  direction,
  topLayerSize,
  size,
  order,
}) {
  invariant.validNumbers(direction, topLayerSize, size, order);

  return direction * this.__sizeToMove({ topLayerSize, size, order });
};

const calculate = new Calculate({ offset: 10, initialOffset: 0 });
