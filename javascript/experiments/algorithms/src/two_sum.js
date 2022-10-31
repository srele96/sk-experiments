// The problem:
//
// Given an array of integers nums and an integer target, return indices of the two numbers such that they add up to target.
//
// You may assume that each input would have exactly one solution, and you may not use the same element twice.
//
// You can return the answer in any order.

// Constraints:
//
//     2 <= nums.length <= 104
//     -109 <= nums[i] <= 109
//     -109 <= target <= 109
//     Only one valid answer exists.

/**
 * @param {number[]} nums
 * @param {number} target
 * @return {number[]}
 */
function two_sum(nums, target) {
  // Save visited element indexes in the Map so we can check if there
  // is a number we need to add to the current one to reach the result.
  // The Map has better performance than a JavaScript object.
  // https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/Map#objects_vs._maps
  const visited_number_index = new Map();
  // Prevent variable redeclaration in the loop.
  let i = 0;
  let length = nums.length;
  let diff = undefined;
  let current_number = undefined;
  let visited_index = undefined;

  for (i; i != length; ++i) {
    current_number = nums[i];
    // Get the number we need to reach the target value.
    // Reduce the element from the sum because the sum is always
    // higher than the other two numbers that make it up.
    diff = target - current_number;

    visited_index = visited_number_index.get(diff);
    // Check for the number we need to reach the target value.
    // Check whether the value is the type of number because of
    // the value of 0 results in false.
    // For example: if(0) is evaluated as if(false).
    if (typeof visited_index === 'number') {
      return [visited_index, i];
    }

    // Save the visited value after all checks because if
    // target - current_value yields the current_value and the
    // current_value is saved above the if statement, we will
    // receive the false positive.
    visited_number_index.set(current_number, i);
  }
}

module.exports.two_sum = two_sum;
