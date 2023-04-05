/**
 * Recursion states:
 *
 * N-th combination is a combination of current number and n-1th combinations
 * of all numbers after it.
 *
 * @param {number} n
 * @param {number[]} list
 * @returns
 */
function combs(n, list) {
  const result = [];
  if (n === 1) {
    for (const n of list) {
      result.push([n]);
    }
  } else {
    for (let i = 0; i <= list.length - n; ++i) {
      const current = list[i];
      const rest = list.slice(i + 1);
      const restCombs = combs(n - 1, rest);
      for (const n of restCombs) {
        n.unshift(current);
        result.push(n);
      }
    }
  }
  return result;
}

/**
 * Recursion states:
 *
 * N-th permutation is a combination of current number and n-1th permutation of
 * all other numbers excluding current one.
 *
 * @param {number} n
 * @param {number[]} list
 * @returns
 */
function perms(n, list) {
  let result = [];
  if (n === 1) {
    for (const val of list) {
      result.push([val]);
    }
  } else {
    for (let i = 0; i != list.length; ++i) {
      const current = list[i];
      const others = [...list.slice(0, i), ...list.slice(i + 1)];
      const othersPerms = perms(n - 1, others);
      for (const otherPerm of othersPerms) {
        otherPerm.unshift(current);
        result.push(otherPerm);
      }
    }
  }
  return result;
}

module.exports.perms = perms;
module.exports.combs = combs;
