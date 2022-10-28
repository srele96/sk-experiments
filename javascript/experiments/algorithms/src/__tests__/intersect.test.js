const { intersect } = require('../intersect');

test(
  'should return the correct intersection using the case from' +
    ' LeetCode example one',
  () => {
    const nums_1 = [1, 2, 2, 1];
    const nums_2 = [2, 2];
    const intersection = [2, 2];

    expect(intersect(nums_1, nums_2)).toEqual(intersection);
  }
);

test(
  'should return the correct intersection using the case from' +
    ' LeetCode example two',
  () => {
    const nums_1 = [4, 9, 5];
    const nums_2 = [9, 4, 9, 8, 4];
    const intersection = [4, 9];

    expect(intersect(nums_1, nums_2)).toEqual(intersection);
  }
);

test(
  'should return the correct intersection where each array has the' +
    ' minimum constrained length with the intersection',
  () => {
    const nums_1 = [1];
    const nums_2 = [1];
    const intersection = [1];

    expect(intersect(nums_1, nums_2)).toEqual(intersection);
  }
);

test(
  'should return an empty intersection where each array has the minimum' +
    ' constrained length without an intersection',
  () => {
    const nums_1 = [2];
    const nums_2 = [1];
    const intersection = [];

    expect(intersect(nums_1, nums_2)).toEqual(intersection);
  }
);

test(
  'should return an empty intersection where each array has a longer' +
    ' length without an intersection',
  () => {
    const nums_1 = [1, 2, 3, 4, 5];
    const nums_2 = [6, 7, 8, 9];
    const intersection = [];

    expect(intersect(nums_1, nums_2)).toEqual(intersection);
  }
);
