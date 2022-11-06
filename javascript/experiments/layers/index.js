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
  withinInclusiveBounds: Object.freeze(function ({ value, begin, end }) {
    if (value < begin || value > end) {
      throw new Error('value out of bounds');
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
  sequences: Object.freeze({
    size: Object.freeze({
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
  }),
  length: 4,
  topLayerIndex: 1,
  offset: 10,
  initialOffset: 0,
});

function produceSequences(sequences, length) {
  invariant.validNumbers(length);

  const initialSequences = {};

  return Object.entries(sequences).reduce(
    (sequences, [key, { initialValue, changeSubsequentBy }]) => {
      sequences[key] = produceSequence({
        initialValue,
        changeSubsequentBy,
        length,
      });

      return sequences;
    },
    initialSequences
  );
}

const sequences = Object.freeze(
  produceSequences(options.sequences, options.length)
);

/**
 * @typedef {{ initialValue: number; changeSubsequentBy: number[] }} Sequence
 *
 * @param {{
 *   sequences: {
 *     size: Sequence;
 *     scale: Sequence;
 *     order: Sequence;
 *     right: Sequence;
 *     left: Sequence;
 *     zIndex: Sequence;
 *   };
 *   length: number;
 *   topLayerIndex: number;
 *   offset: number;
 *   initialOffset: number;
 * }} options
 */
function Layers(options) {
  const validOptions = Object.freeze([
    'sequences',
    'length',
    'topLayerIndex',
    'offset',
    'initialOffset',
  ]);
  invariant.validOptions(options, validOptions);

  const { sequences, length, topLayerIndex, offset, initialOffset } = options;
  invariant.validNumbers(length, topLayerIndex, offset, initialOffset);

  const validSequences = Object.freeze([
    'size',
    'scale',
    'order',
    'right',
    'left',
    'zIndex',
  ]);
  invariant.validOptions(sequences, validSequences);

  this.__sequences = Object.freeze(produceSequences(sequences, length));
  this.__options = options;
}

Layers.prototype.getLayers = function (topLayerIndex) {
  const includeLastIndex = 1;
  invariant.validNumbers(topLayerIndex);
  invariant.withinInclusiveBounds({
    value: topLayerIndex,
    begin: 0,
    end: this.__options.length - includeLastIndex,
  });

  const layers = new Array(this.__options.length);

  const assign = ({ byOrder, direction }) => ({
    size: sequences.size[byOrder],
    scale: sequences.scale[byOrder],
    order: sequences.order[byOrder],
    zIndex: sequences.zIndex[byOrder],
    direction: direction[byOrder],

    topLayerIndex,
    topLayerSize: options.sequences.size.initialValue,
    offset: options.offset,
    initialOffset: options.initialOffset,
  });

  let i = topLayerIndex;
  let byOrder = 0;
  while (i >= 0) {
    layers[i] = assign({ byOrder, direction: this.__sequences.left });
    ++byOrder;
    --i;
  }

  i = topLayerIndex;
  byOrder = 0;
  while (i != layers.length) {
    layers[i] = assign({ byOrder, direction: this.__sequences.right });

    ++byOrder;
    ++i;
  }

  i = 0;
  while (i != layers.length) {
    layers[i].index = i;
    ++i;
  }

  return layers;
};

const layers = new Layers(options);
console.log(layers.getLayers(1));

const layersWithWings = new Layers({ ...options, initialOffset: 80 });
console.log(layersWithWings.getLayers(3));
