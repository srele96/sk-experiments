#include <bits/stdc++.h>
using namespace std;

namespace workingSolution {

// Sadly, this solution beats only 8.04% by runtime and memory usage... Poor.

// The only clue i work with for now is this
// We don't have constraint minSum > t
// So maybe trying the local best choice will speed up the algorithm and we can
// avoid TLE Aaaaand I was correct. I was led to these ideas thanks to solving
// this problem: leetcode.com/problems/maximum-weighted-k-edge-path
class Solution {
 public:
  int minPathCost(vector<vector<int>>& grid, vector<vector<int>>& moveCost) {
    int m = grid.size() - 1, n = grid[0].size() - 1;
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, INT_MAX));
    function<int(int, int)> fn = [&](int i, int j) {
      if (i == m) return grid[i][j];
      if (dp[i][j] != INT_MAX) return dp[i][j];
      int r = INT_MAX;
      for (int c = 0; c <= n; ++c) {
        r = min(r, moveCost[grid[i][j]][c] + grid[i][j] + fn(i + 1, c));
      }
      return dp[i][j] = r;
    };
    int r = INT_MAX;
    for (int c = 0; c <= n; ++c) {
      r = min(r, fn(0, c));
    }
    return r;
  }
};

}  // namespace workingSolution

namespace tleRegardlessOfCaching {

class Solution {
 public:
  int minPathCost(vector<vector<int>>& grid, vector<vector<int>>& moveCost) {
    int m = grid.size() - 1, n = grid[0].size() - 1;
    vector<vector<unordered_map<int, int>>> dp(
        m + 1, vector<unordered_map<int, int>>(n + 1));
    function<int(int, int, int)> fn = [&](int i, int j, int s) {
      if (i == m) return s + grid[i][j];
      if (dp[i][j].find(s) != dp[i][j].end()) {
        return dp[i][j][s];
      }
      int r = INT_MAX;
      for (int c = 0; c <= n; ++c) {
        r = min(r, fn(i + 1, c, s + grid[i][j] + moveCost[grid[i][j]][c]));
      }
      return dp[i][j][s] = r;
    };
    int r = INT_MAX;
    for (int c = 0; c <= n; ++c) {
      r = min(r, fn(0, c, 0));
    }
    // for(int i = 0; i <= m; ++i) {
    //   for(int j = 0; j <= n; ++j) {
    //     cout << "dp[" << i << "][" << j << "][";
    //     for(auto& [s, arr] : dp[i][j]) {
    //       cout << s << "]: ";
    //       for(int v : arr) {
    //         cout << v << ", ";
    //       }
    //       cout << "\n";
    //     }
    //     cout << "\n";
    //   }
    // }
    return r;
  }
};

}  // namespace tleRegardlessOfCaching
