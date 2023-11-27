/**
 * @param {string} s
 * @return {number}
 */
function longest_substring(s) {
  let max = 0,
    left = 0,
    right = 0,
    chars = new Map(),
    size = 0;
  while (right < s.length) {
    c = s.charAt(right);
    chars.set(c, chars.has(c) ? chars.get(c) + 1 : 1);
    ++size;
    ++right;
    if (chars.size === size) {
      max = Math.max(max, size);
    }
    while (chars.size < size) {
      c = s.charAt(left);
      chars.set(c, chars.get(c) - 1);
      chars.get(c) === 0 && chars.delete(c);
      ++left;
      --size;
    }
  }
  return max;
}

module.exports.longest_substring = longest_substring;
