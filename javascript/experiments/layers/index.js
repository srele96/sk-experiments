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

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

function produceSequence({ initialValue, changeSubsequentBy, length }) {
  invariant.validNumbers(initialValue, length);
  invariant.validNumbers(...changeSubsequentBy);
  invariant.validArray(changeSubsequentBy);
  invariant.lengthEqualOrLess(changeSubsequentBy, length);

  let initialValue_DontModifyArgument = initialValue;
  let changeSubsequentBy_DontModifyArgument = changeSubsequentBy.slice();
  let change = 0;

  const sequence = new Array(length);

  for (let i = 0; i != length; ++i) {
    initialValue_DontModifyArgument += change;
    sequence[i] = initialValue_DontModifyArgument;

    if (changeSubsequentBy_DontModifyArgument.length > 0) {
      change = changeSubsequentBy_DontModifyArgument.shift();
    }
  }

  return sequence;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

const options = Object.freeze({
  topLayerSize: Object.freeze({
    initialValue: 100,
    changeSubsequentBy: Object.freeze([-20, -10]),
  }),
  scale: Object.freeze({
    initialValue: 1,
    changeSubsequentBy: Object.freeze([-0.2, -0.1]),
  }),
  order: Object.freeze({
    initialValue: 0,
    changeSubsequentBy: Object.freeze([1]),
  }),
  right: Object.freeze({
    initialValue: 0,
    changeSubsequentBy: Object.freeze([1, 0]),
  }),
  left: Object.freeze({
    initialValue: 0,
    changeSubsequentBy: Object.freeze([-1, 0]),
  }),
  zIndex: Object.freeze({
    initialValue: 8,
    changeSubsequentBy: Object.freeze([-1]),
  }),
  length: 4,
  topLayerIndex: 1,
  offset: 10,
  initialOffset: 0,
});

const size = produceSequence({
  initialValue: options.topLayerSize.initialValue,
  changeSubsequentBy: options.topLayerSize.changeSubsequentBy,
  length: options.length,
});
const scale = produceSequence({
  initialValue: options.scale.initialValue,
  changeSubsequentBy: options.scale.changeSubsequentBy,
  length: options.length,
});
const order = produceSequence({
  initialValue: options.order.initialValue,
  changeSubsequentBy: options.order.changeSubsequentBy,
  length: options.length,
});
const right = produceSequence({
  initialValue: options.right.initialValue,
  changeSubsequentBy: options.right.changeSubsequentBy,
  length: options.length,
});
const left = produceSequence({
  initialValue: options.left.initialValue,
  changeSubsequentBy: options.left.changeSubsequentBy,
  length: options.length,
});
const zIndex = produceSequence({
  initialValue: options.zIndex.initialValue,
  changeSubsequentBy: options.zIndex.changeSubsequentBy,
  length: options.length,
});

const assign = (i, direction) => ({
  size: size[i],
  scale: scale[i],
  order: order[i],
  zIndex: zIndex[i],
  direction: direction[i],
});

const layers = new Array(options.length);

let i = options.topLayerIndex;
let byOrder = 0;
while (i >= 0) {
  layers[i] = {
    size: size[byOrder],
    scale: scale[byOrder],
    order: order[byOrder],
    zIndex: zIndex[byOrder],

    direction: left[byOrder],
  };

  ++byOrder;
  --i;
}

i = options.topLayerIndex;
byOrder = 0;
while (i != layers.length) {
  layers[i] = {
    size: size[byOrder],
    scale: scale[byOrder],
    order: order[byOrder],
    zIndex: zIndex[byOrder],

    direction: right[byOrder],
  };

  ++byOrder;
  ++i;
}

i = 0;
while (i != layers.length) {
  layers[i] = {
    ...layers[i],

    index: i,
    topLayerSize: options.topLayerSize.initialValue,
    topLayerIndex: options.topLayerIndex,
    offset: options.offset,
    initialOffset: options.initialOffset,
  };
  ++i;
}

console.log(layers);
