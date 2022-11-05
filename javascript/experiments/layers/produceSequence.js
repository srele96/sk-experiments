function produceSequence({ initialValue, changeSubsequentBy, length }) {
  invariant.validNumbers(initialValue, length);
  invariant.validNumbers(...changeSubsequentBy);
  invariant.validArray(changeSubsequentBy);
  invariant.lengthEqualOrLess(changeSubsequentBy, length);

  // verify initialValue is a number
  // verify length is a number
  // verify changeSubsequentBy is an array of length less than or equal to length of the sequence
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

produceSequence({ initialValue: 10, changeSubsequentBy: [1], length: 8 });

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
