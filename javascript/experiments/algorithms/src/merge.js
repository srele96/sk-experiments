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
  const left = new Array(m);
  // Create a copy of valid elements to be able to perform a clean merge and
  // use the first array as a result.
  for (let i = 0; i != m; ++i) {
    left[i] = nums1[i];
  }

  let left_accessor = 0;
  let right_accessor = 0;
  let insertion_index = 0;

  // Merge copied and second arrays and use the first one as a result.
  while (true) {
    // Each of the arrays initially may not contain any numbers. In addition,
    // each of the indexes may reach the end before we finish iterating over
    // the other. These two make me unable to know which array element I may
    // access. Therefore, I check at each iteration to see if either of the
    // accessors has reached the end.
    if (left_accessor != m && right_accessor != n) {
      if (left[left_accessor] < nums2[right_accessor]) {
        nums1[insertion_index] = left[left_accessor];
        ++left_accessor;
      } else {
        nums1[insertion_index] = nums2[right_accessor];
        ++right_accessor;
      }
      ++insertion_index;
    } else if (left_accessor != m) {
      nums1[insertion_index] = left[left_accessor];
      ++left_accessor;
      ++insertion_index;
    } else if (right_accessor != n) {
      nums1[insertion_index] = nums2[right_accessor];
      ++right_accessor;
      ++insertion_index;
    } else {
      break;
    }
  }
}

module.exports.merge = merge;
