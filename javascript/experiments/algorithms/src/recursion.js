/**
 * Recursion states:
 *
 * N-th combination is a combination of current number and n-1th combinations
 * of all numbers after it.
 *
 * T(1, m) = m
 * T(n, m) = (m - n) * (T(n - 1, m - 1) + m - 1)
 *
 * @param {number} n
 * @param {number[]} list
 * @returns
 */
function combs(n, list) {
  const result = [];
  if (n === 1) {
    // m
    for (const n of list) {
      result.push([n]);
    }
  } else {
    // m - n
    for (let i = 0; i <= list.length - n; ++i) {
      const current = list[i];
      const rest = list.slice(i + 1);
      // Not sure how to represent this one. With each next iteration we have
      // one less element here, not only based on m-1 but we cut off all
      // previous elements.
      const restCombs = combs(n - 1, rest);
      // Same here, not sure how to represent this runtime.
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
 * T(1, m) = n
 * T(n, m) = n * (T(n - 1, m - 1) + m - 1)
 *
 * @param {number} n
 * @param {number[]} list
 * @returns
 */
// T(n, m)
function perms(n, list) {
  let result = [];
  if (n === 1) {
    // m
    for (const val of list) {
      result.push([val]);
    }
  } else {
    // m
    for (let i = 0; i != list.length; ++i) {
      const current = list[i];
      // Ignore slice runtime, while in reality it is not a free operation.
      const others = [...list.slice(0, i), ...list.slice(i + 1)];
      // T(n - 1, m - 1)
      const othersPerms = perms(n - 1, others);
      // (m - 1)
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
