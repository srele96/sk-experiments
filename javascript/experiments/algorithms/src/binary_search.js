// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Binary Search Solution Explanation
//
// Binary search checks if the current element is the one we need and returns
// the index (a way to access it).
//
// Otherwise, if our number is higher, we repeat this function call with begin
// value being the adjacent value to the right from the index we currently
// checked (one index higher).
//
// Otherwise, we repeat the function call to the left.
//
// If the previous steps fail and begin is larger than the end, we return an
// identification that we did not find the element.
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// How do we find the mid-value between the two values?
//
//   * from value - to value
//   * begin - end
//
// The formula: mid = floor((end - begin) / 2) + begin
//
// We use the begin value as a starting point to explain why the formula works.
//
// Then we calculate the length from the end to begin.
//
// We reduce begin from the end because the end is bigger and the difference in
// length. For example, five minus three is two; therefore, our distance is
// two.
//
// Halve the length and floor the remainder. I am trying to remember precisely
// why we have to floor that value, but I wanted to ceil it, resulting in an
// infinite loop - the values never cross. However, we surely can make ceil
// work too.
//
// Using the floor on the remainder yields the mid-value of the two. Once we
// have an offset and length to center from beginning to end, we have the
// center's value.
//
// An offset is a different word for begin. If begin value is 0, the offset is
// 0. A begin 5 is an offset 5. Offset from the starting point.
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Cache values not to recreate them in the recursion.
const did_not_find = -1;
const to_left = -1;
const to_right = 1;

let half = undefined;
let current_number = undefined;

function binary_search(numbers, begin, end, value) {
  if (begin < end) {
    // Use math formula to calculate the index between two values.
    half = Math.floor((end - begin) / 2) + begin;
    current_number = numbers[half];

    if (current_number === value) {
      return half;
    } else if (current_number < value) {
      return binary_search(numbers, half + to_right, end, value);
    } else {
      return binary_search(numbers, begin, half + to_left, value);
    }
  } else {
    return did_not_find;
  }
}

module.exports.binary_search = binary_search;
