'use strict';

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
