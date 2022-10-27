const { merge } = require('../merge');

test('merges two arrays correctly with positive values', () => {
  const nums1 = [1, 2, 3, 0, 0, 0];
  const m = 3;
  const nums2 = [2, 5, 6];
  const n = 3;

  merge(nums1, m, nums2, n);

  expect(nums1).toEqual([1, 2, 2, 3, 5, 6]);
});

test('merges two arrays correctly with empty second array', () => {
  const nums1 = [1];
  const m = 1;
  const nums2 = [];
  const n = 0;

  merge(nums1, m, nums2, n);

  expect(nums1).toEqual([1]);
});

test('merges two arrays correctly with empty first array', () => {
  const nums1 = [0];
  const m = 0;
  const nums2 = [5];
  const n = 1;

  merge(nums1, m, nums2, n);

  expect(nums1).toEqual([5]);
});

test('merges two arrays correctly with a negative value', () => {
  const nums1 = [-5, 10, 15, 20, 0];
  const m = 4;
  const nums2 = [-100];
  const n = 1;

  merge(nums1, m, nums2, n);

  expect(nums1).toEqual([-100, -5, 10, 15, 20]);
});
