#include <bits/stdc++.h>
using namespace std;

// https://leetcode.com/problems/minimum-path-sum/

namespace top_down {

class Solution {
 public:
  int minPathSum(vector<vector<int>>& grid) {
    vector<vector<int>> dp(grid.size(), vector<int>(grid[0].size(), -1));
    dp[0][0] = grid[0][0];

    function<int(int, int)> solve{[&](int m, int n) {
      if (dp[m][n] != -1) {
        return dp[m][n];
      }
      if (m == 0 && n == 0) {
        // can not reduce either
        grid[m][n];
        dp[m][n] = grid[m][n];
        return dp[m][n];
      } else if (m == 0) {
        // n can be reduced
        dp[m][n] = grid[m][n] + solve(m, n - 1);
        return dp[m][n];
      } else if (n == 0) {
        // m can be reduced
        dp[m][n] = grid[m][n] + solve(m - 1, n);
        return dp[m][n];
      } else {
        // calculate the min
        dp[m][n] = grid[m][n] + min(solve(m - 1, n), solve(m, n - 1));
        return dp[m][n];
      }
    }};

    return solve(grid.size() - 1, grid[0].size() - 1);
  }
};

}  // namespace top_down

namespace bottom_up {

class Solution {
 public:
  int minPathSum(vector<vector<int>>& grid) {
    vector<vector<int>> dp(grid.size(), vector<int>(grid[0].size(), -1));

    for (int m = 0; m < grid.size(); ++m) {
      for (int n = 0; n < grid[m].size(); ++n) {
        if (m > 0 && n > 0) {
          dp[m][n] = grid[m][n] + min(dp[m - 1][n], dp[m][n - 1]);
        } else if (m > 0) {
          dp[m][n] = grid[m][n] + dp[m - 1][n];
        } else if (n > 0) {
          dp[m][n] = grid[m][n] + dp[m][n - 1];
        } else {
          dp[m][n] = grid[m][n];
        }
      }
    }

    return dp[dp.size() - 1][dp[0].size() - 1];
  }
};

}  // namespace bottom_up
