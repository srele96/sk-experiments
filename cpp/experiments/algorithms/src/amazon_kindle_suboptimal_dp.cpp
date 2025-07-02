#include <bits/stdc++.h>

using namespace std;

// https://www.reddit.com/r/leetcode/comments/1lo5fpp/help_me_solve_is_amazon_oa_question/#lightbox

class Solution {
 public:
  /**
   * Amazon Kindle Books Problem
   *
   * Given:
   * - n books with costs cost[i]
   * - pairCost: cost to buy leftmost and rightmost books together
   * - k: maximum number of times pairCost can be used
   *
   * Operations:
   * 1. Buy leftmost book individually for cost[0] (removes from sequence)
   * 2. Buy rightmost book individually for cost[n-1] (removes from sequence)
   * 3. Buy leftmost AND rightmost together for pairCost (removes both, uses 1
   * of k operations)
   *
   * Find minimum cost to purchase all books.
   *
   * @param cost: vector of book costs
   * @param pairCost: cost to buy leftmost and rightmost together
   * @param k: maximum number of times pairCost operation can be used
   * @return minimum total cost to buy all books
   */
  long long findMinPrice(vector<int>& cost, int pairCost, int k) {
    // ------------------------------------------------------------------------
    // ------------------------------------------------------------------------

    /**
     * @brief Solved by me. The template mostly AI generated. I added some edge
     * cases that I later needed. The code within this function is by me. If
     * that matters... at all...
     *
     * The solution is not optimal, but I solely focus on DP solutions
     * temporarily our of my own... whatever.
     */

    // ------------------------------------------------------------------------
    // ------------------------------------------------------------------------

    int n = cost.size();

    vector<vector<vector<long long>>> dp(
        k + 1, vector<vector<long long>>(cost.size(),
                                         vector<long long>(cost.size(), -1)));

    function<long long(int, int, int)> f = [&](int i, int j,
                                               int t) -> long long {
      if (i > j) return 0;
      if (i == j) return cost[i];

      if (dp[t][i][j] != -1) return dp[t][i][j];

      long long r = LLONG_MAX;

      if (t > 0) {
        r = min(r, pairCost + f(i + 1, j - 1, t - 1));
        r = min(r, cost[i] + f(i + 1, j, t));
        r = min(r, cost[j] + f(i, j - 1, t));
      } else {
        r = min(r, cost[i] + f(i + 1, j, t));
      }

      return dp[t][i][j] = r;
    };

    long long result = f(0, n - 1, k);

    return result;
  }
};

class TestRunner {
 private:
  int testsPassed = 0;
  int totalTests = 0;

  void runTest(vector<int> cost, int pairCost, int k, long long expected,
               string testName) {
    totalTests++;
    cout << "Running " << testName << "... ";

    auto start = chrono::high_resolution_clock::now();
    Solution solution;
    long long result = solution.findMinPrice(cost, pairCost, k);
    auto end = chrono::high_resolution_clock::now();

    auto duration = chrono::duration_cast<chrono::microseconds>(end - start);

    if (result == expected) {
      cout << "✅ PASS (" << duration.count() << "μs)" << endl;
      testsPassed++;
    } else {
      cout << "❌ FAIL" << endl;
      cout << "  Input: cost = [";
      for (int i = 0; i < cost.size(); i++) {
        cout << cost[i];
        if (i < cost.size() - 1) cout << ", ";
      }
      cout << "], pairCost = " << pairCost << ", k = " << k << endl;
      cout << "  Expected: " << expected << endl;
      cout << "  Got: " << result << endl;
      cout << "  Difference: " << (result - expected) << endl;
    }
  }

 public:
  void runAllTests() {
    cout << "=== Amazon Kindle Books Problem Test Suite ===" << endl;
    cout << "Problem: Find minimum cost to buy all books with limited pair "
            "operations"
         << endl;
    cout << endl;

    // Sample Case 0 from HackerRank
    runTest({1, 1, 1}, 3, 1, 3, "HackerRank Sample 0");

    // Sample Case 1 from HackerRank
    runTest({9, 11, 13, 15, 17}, 6, 2, 21, "HackerRank Sample 1");

    // Edge case: single book
    runTest({5}, 10, 1, 5, "Single book");

    // Edge case: two books, pair is better
    runTest({10, 20}, 15, 1, 15, "Two books - pair better");

    // Edge case: two books, individual better
    runTest({1, 2}, 10, 1, 3, "Two books - individual better");

    // Edge case: k = 0 (no pair operations allowed)
    runTest({1, 5, 3, 7}, 2, 0, 16, "No pair operations allowed");

    // Edge case: k >= n/2 (unlimited pairs effectively)
    runTest({10, 1, 2, 20}, 5, 10, 8, "Unlimited pairs");

    // All same costs
    runTest({5, 5, 5, 5}, 8, 2, 16, "All same costs");

    // Large costs, cheap pairs
    runTest({1000, 999, 998, 997}, 1, 2, 2, "Expensive books, cheap pairs");

    // Small costs, expensive pairs
    runTest({1, 2, 3, 4}, 100, 2, 10, "Cheap books, expensive pairs");

    // Odd number of books
    runTest({1, 10, 2, 8, 3}, 5, 2, 11, "Odd number of books");

    // k = 1 with multiple books
    runTest({5, 1, 8, 2, 6}, 4, 1, 12, "Limited to 1 pair operation");

    // Alternating high-low costs
    runTest({100, 1, 99, 2, 98}, 10, 2, 21, "Alternating costs");

    // Edge case: very large k
    runTest({1, 2, 3, 4, 5, 6}, 3, 1000, 9, "Very large k");

    runTest({6, 5, 4, 3, 2, 1}, 2, 2, 7, "Has to buy from the right");

    runTest({1, 100, 1, 100, 1}, 50, 1, 53, "Alternating costs II");

    cout << endl;
    cout << "=== Test Results ===" << endl;
    cout << "Passed: " << testsPassed << "/" << totalTests << " tests" << endl;

    if (testsPassed == totalTests) {
      cout << "🎉 ALL TESTS PASSED! Your solution is working correctly!"
           << endl;
      cout << "💡 Ready for submission to HackerRank!" << endl;
    } else {
      cout << "❌ SOME TESTS FAILED" << endl;
      cout << "🔍 Check your algorithm logic and edge cases" << endl;
      cout << "💭 Consider: when is it optimal to use pair operations vs "
              "individual purchases?"
           << endl;
    }

    // Performance note
    if (testsPassed == totalTests) {
      cout << endl;
      cout << "🚀 Performance Note:" << endl;
      cout << "Your solution should handle n ≤ 10^5 in O(n log n) time" << endl;
      cout << "Current tests are small-scale for correctness verification"
           << endl;
    }
  }
};

int main() {
  TestRunner runner;
  runner.runAllTests();
  return 0;
}

/*
=== PROBLEM ANALYSIS ===

From the HackerRank images, this problem has these key characteristics:

1. **Operations Available:**
   - Buy leftmost book individually: cost[0]
   - Buy rightmost book individually: cost[n-1]
   - Buy leftmost AND rightmost as pair: pairCost (limited to k times)

2. **Constraints:**
   - 1 ≤ n ≤ 10^5
   - 1 ≤ pairCost ≤ 10^9
   - 1 ≤ k ≤ n
   - 1 ≤ cost[i] ≤ 10^9
   - Array may NOT be in increasing order

3. **Key Insights:**
   - This is NOT about sorting - order matters (leftmost/rightmost)
   - Limited pair operations (k) adds constraint
   - Need to decide optimally when to use pair vs individual
   - O(n log n) suggests DP with optimization or greedy with sorting of some
derived values

4. **Sample Analysis:**
   - cost = [9, 11, 13, 15, 17], pairCost = 6, k = 2
   - Optimal: pair(9,17)=6 + pair(11,15)=6 + individual(13)=13 = 21
   - Shows that using all available pair operations can be optimal

5. **Algorithm Approach:**
   - Consider: when is pair better than two individuals?
   - pairCost < cost[left] + cost[right] → use pair
   - Limited k means we need to choose best k pairs
   - Possibly sort by savings: (cost[i] + cost[j] - pairCost) and take top k?

6. **Edge Cases to Handle:**
   - k = 0 (no pairs allowed)
   - k ≥ n/2 (effectively unlimited pairs)
   - Single book (n = 1)
   - Two books (n = 2)
   - All books same cost
   - Very expensive/cheap pairCost relative to individual costs
*/
