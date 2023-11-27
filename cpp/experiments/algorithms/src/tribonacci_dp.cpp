#include <bits/stdc++.h>
using namespace std;

// https://leetcode.com/problems/n-th-tribonacci-number/submissions/

namespace one {

class Solution {
 public:
  int tribonacci(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    if (n == 2) return 1;
    int dp[38];
    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 1;
    for (int i{3}; i <= n; ++i) dp[i] = dp[i - 1] + dp[i - 2] + dp[i - 3];
    return dp[n];
  }
};

}  // namespace one

namespace two {

class Solution {
 public:
  vector<int> dp;
  Solution() : dp{vector<int>(38, -1)} {
    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 1;
  }
  int tribonacci(int n) {
    if (dp[n] != -1) return dp[n];
    dp[n] = tribonacci(n - 1) + tribonacci(n - 2) + tribonacci(n - 3);
    return dp[n];
  }
};

}  // namespace two
