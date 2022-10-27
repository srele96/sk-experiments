// You are given two integer arrays nums1 and nums2, sorted in non-decreasing
// order, and two integers m and n, representing the number of elements in
// nums1 and nums2 respectively.
//
// Merge nums1 and nums2 into a single array sorted in non-decreasing order.
//
// The final sorted array should not be returned by the function, but instead
// be stored inside the array nums1. To accommodate this, nums1 has a length
// of m + n, where the first m elements denote the elements that should be
// merged, and the last n elements are set to 0 and should be ignored. nums2
// has a length of n.

/**
 * @param {number[]} nums1
 * @param {number} m
 * @param {number[]} nums2
 * @param {number} n
 * @return {void} Do not return anything, modify nums1 in-place instead.
 */
function merge(nums1, m, nums2, n) {
  const left = new Array(m + 1);
  // Constraint that allows me to use this sentinel
  // -Math.pow(10,9) <= nums1[i], nums2[j] <= Math.pow(10,9)
  const sentinel = Math.pow(10, 9) + 1;
  left[left.length - 1] = sentinel;
  nums2.push(sentinel);
  // Create a copy of valid elements to be able to perform a clean merge and
  // use the first array as a result.
  for (let i = 0; i != m; ++i) {
    left[i] = nums1[i];
  }

  let left_accessor = 0;
  let right_accessor = 0;

  // Merge copied and second arrays and use the first one as a result.
  for (let i = 0; i != m + n; ++i) {
    if (left[left_accessor] < nums2[right_accessor]) {
      nums1[i] = left[left_accessor];
      ++left_accessor;
    } else {
      nums1[i] = nums2[right_accessor];
      ++right_accessor;
    }
  }
}

module.exports.merge = merge;
