// TODO: Use underscores instead of camelCase to follow the rest of the code.

const numbers = new Array();

function getParentIndex(index) {
  return Math.floor((index - 1) / 2);
}

function getLeftChildIndex(index) {
  return 2 * index + 1;
}

function getRightChildIndex(index) {
  return 2 * index + 2;
}

function getChildIndex(index) {
  return {
    left: getLeftChildIndex(index),
    right: getRightChildIndex(index),
  };
}

function peek() {
  return numbers.length > 0 ? numbers[0] : null;
}

function swap({ firstIndex, secondIndex }) {
  const temporary = numbers[firstIndex];
  numbers[firstIndex] = numbers[secondIndex];
  numbers[secondIndex] = temporary;
}

function parentViolatesHeapProperty({ parentNumberIndex, childNumberIndex }) {
  return numbers[parentNumberIndex] > numbers[childNumberIndex];
}

function isWithinBeginBound(index) {
  return index >= 0;
}

function siftUp() {
  let currentNumberIndex = numbers.length - 1;
  let parentNumberIndex = getParentIndex(currentNumberIndex);

  while (
    isWithinBeginBound(currentNumberIndex) &&
    parentViolatesHeapProperty({
      parentNumberIndex,
      childNumberIndex: currentNumberIndex,
    })
  ) {
    swap({ firstIndex: parentNumberIndex, secondIndex: currentNumberIndex });

    // Next
    currentNumberIndex = parentNumberIndex;
    parentNumberIndex = getParentIndex(currentNumberIndex);
  }
}

function push(number) {
  numbers.push(number);
  siftUp();
}

function isWithinEndBound(index) {
  const lastIndex = numbers.length - 1;

  return index <= lastIndex;
}

function getIndexOfSmallerNumber({ leftChildIndex, rightChildIndex }) {
  if (isWithinEndBound(rightChildIndex)) {
    if (numbers[leftChildIndex] < numbers[rightChildIndex]) {
      return leftChildIndex;
    } else {
      return rightChildIndex;
    }
  } else if (isWithinEndBound(leftChildIndex)) {
    return leftChildIndex;
  } else {
    throw new Error('Child index is out of bounds.');
  }
}

function siftDown() {
  let currentNumberIndex = 0;
  let childIndex = getChildIndex(currentNumberIndex);

  while (isWithinEndBound(childIndex.left)) {
    let smallerNumberIndex = getIndexOfSmallerNumber({
      leftChildIndex: childIndex.left,
      rightChildIndex: childIndex.right,
    });

    if (
      parentViolatesHeapProperty({
        parentNumberIndex: currentNumberIndex,
        childNumberIndex: smallerNumberIndex,
      })
    ) {
      swap({ firstIndex: currentNumberIndex, secondIndex: smallerNumberIndex });

      // Next
      currentNumberIndex = smallerNumberIndex;
      childIndex = getChildIndex(currentNumberIndex);
    } else {
      break;
    }
  }
}

function pop() {
  if (numbers.length === 0) {
    // Semantically same as array.pop()
    return undefined;
  } else {
    let firstNumber = numbers[0];
    // Make last number as the first
    numbers[0] = numbers[numbers.length - 1];
    // Remove the last element
    numbers.pop();
    siftDown();

    return firstNumber;
  }
}

function getHeapNumbers() {
  return numbers;
}

module.exports.getHeapNumbers = getHeapNumbers;
module.exports.push = push;
module.exports.pop = pop;
module.exports.peek = peek;
