// The solution
//
// I need to collect common pairs from the two arrays.
//
// I am storing each array in the left and right segments. So I go through the
// first segment and memorize the count of each unique value.
//
// While going through the second segment, I check if I have seen the current
// value in the other one.
//
// When I find a value, I will take it out and save it among common values.
//
// To collect common pairs from two arrays, I need to check if I have seen such
// an element in the other segment. Then, take it from both memories and save
// it in common elements.
//
// If I don't find it, I can proceed because I am sure the current value does
// not have a pair. If I see this value again, I won't have a match for it, so
// I don't need to save it. That means I don't need to keep any values from
// this set.
//
// Count occurrences of each unique value.

/**
 * @param {number[]} nums1
 * @param {number[]} nums2
 * @return {number[]}
 */
function intersect(nums1, nums2) {
  const memory = new Map();
  const intersection = [];

  for (let i = nums1.length - 1; i >= 0; --i) {
    if (typeof memory[nums1[i]] === 'number') {
      ++memory[nums1[i]];
    } else {
      memory[nums1[i]] = 1;
    }
  }

  for (let i = nums2.length - 1; i >= 0; --i) {
    if (memory[nums2[i]] > 0) {
      --memory[nums2[i]];
      intersection.push(nums2[i]);
    }
  }

  return intersection;
}

module.exports.intersect = intersect;
