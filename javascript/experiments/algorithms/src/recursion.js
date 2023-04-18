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

/**
 * Recurrence relation:
 *
 * T(1) = 1
 * T(n) = T(n-1)
 *
 * @param {number} larger
 * @param {number} smaller
 * @returns {number}
 */
function gcd(larger, smaller) {
  // smaller is previous remainder
  let remainder = larger % smaller;
  return remainder === 0 ? smaller : gcd(smaller, remainder);
}

/**
 * Recurrence relation:
 *
 * T(1) = 1
 * T(n) = T(n-1)
 *
 * @param {string} str
 * @returns
 */
const reverse = (str) =>
  str.length === 0 ? str : reverse(str.substr(1)) + str.charAt(0);

// Problem description:
//
// Having ladders of n steps, a person climbing them is allowed to
// climb one or two steps at a time, a step two must be followed by
// a step one, while step one may be followed by step one
// for example, here are valid ways to climb a ladder of 3 steps:
// one, one, one
// one, two
// two, one
//
// Recursion states:
// - A ladder of length 0 has no way to climb it hence an empty set of steps
// - A ladder of length 1 has only one way to climb it, hence an empty set of 1
// step
// - A ladder of n steps is climable by:
//   - For each n-1th set of steps append 1
//   - For each n-2th set of steps if last step is not 2 then append 2
// IMPORTANT:
// The reason we check if the last number is two, take for an example set of
// steps when n=2, we have [1,1], [2], when we have to generate steps for
// ladder of length n=4, for every n-1 we will append 1, which means for each
// combination of steps for n=3 we append 1. Then, for every n-2, we will
// append 2. If we take a closer look n=2 has [1,1], [2] and if we append to
// each of them a step 2 without performing a check, we will end up
// with: [1,1,2], [2,2] which will yield one valid and one invalid step [2,2].
// There might be a better solution but I didn't have a reason to search for
// another one.
// For example:
// n = 0
// []
// ----
// n = 1
// [1]
// ----
// n = 2
// [1,1]     - For each n-1 append 1
// [2]       - For each n-2 append 2
// ----
// n = 3
// [1,1,1]   - For each n-1 append 1
// [2,1]     - For each n-1 append 1
// [1,2]     - For each n-2 if last is not 2 then append 2
// ----
// n = 4
// [1,1,1,1] - For each n-1 append 1
// [2,1,1]   - For each n-1 append 1
// [1,2,1]   - For each n-1 append 1
// [1,1,2]   - For each n-2 if last is not 2 then append 2
// -- here we ignore [1,2] because last is 2
function generateLadderSteps(n) {
  let combinationOfSteps = [];

  if (n === 0) combinationOfSteps.push([]);
  else if (n === 1) combinationOfSteps.push([1]);
  else {
    for (const steps of generateLadderSteps(n - 1)) {
      steps.push(1);
      combinationOfSteps.push(steps);
    }
    for (const steps of generateLadderSteps(n - 2)) {
      if (steps[steps.length - 1] !== 2) {
        steps.push(2);
        combinationOfSteps.push(steps);
      }
    }
  }

  return combinationOfSteps;
}

function TreeNode(val = 0, left = null, right = null) {
  this.val = val;
  this.left = left;
  this.right = right;
}

/**
 * Make sure to call like: combsFBT()(3). Do not use like:
 * const generateCombs = combsFBT();
 * generateCombs(3);
 * Because that will use stale memoized state between multiple calls.
 * Yeah, I know... poor design! Who cares, only I will use it probably
 * never.
 */
function combsFBT() {
  // Wrap memoized state to provide fresh memoization every time we
  // generate full binary trees.
  const memo = new Map();
  memo.set(1, [new TreeNode()]);

  return function _combsFBT(n) {
    if (n % 2 === 0) return [];
    if (!memo.has(n)) {
      let combs = [];
      // Make sure not to receive even number because **I THINK**
      // it will terminate recursion as the solution is designed
      // to skip even numbers.
      // Start from n-2 and iterate over odd numbers.
      // The loop generates for n=5:
      // i=3 j=1
      // i=1 j=3
      // The loop generates for n=7:
      // i=5 j=1
      // i=3 j=3
      // i=1 j=5
      // The loop merges left and right three of `i` and `j`
      for (let i = n - 2; i >= 0; i -= 2) {
        // Start from 1 and increase by 2.
        const j = n - i - 1;
        for (const leftTree of _combsFBT(i)) {
          for (const rightTree of _combsFBT(j)) {
            combs.push(new TreeNode(0, leftTree, rightTree));
          }
        }
      }
      memo.set(n, combs);
    }
    return memo.get(n);
  };
}

module.exports.perms = perms;
module.exports.combs = combs;
module.exports.gcd = gcd;
module.exports.reverse = reverse;
module.exports.generateLadderSteps = generateLadderSteps;
module.exports.TreeNode = TreeNode;
module.exports.combsFBT = combsFBT;
