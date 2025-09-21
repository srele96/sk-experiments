#include <bits/stdc++.h>
using namespace std;

// https://leetcode.com/problems/triangle/description/

// Apparently this solution is inefficient
// compared to other solutions
// Both: TopDown and BottomUp are
// quite slow
namespace bottomUp {

class Solution {
 public:
  int minimumTotal(vector<vector<int>>& t) {
    vector<vector<int>> dp(201, vector<int>(201));
    for (auto& e : dp[t.size()]) e = 0;
    for (int i = t.size() - 1; i >= 0; --i) {
      for (int j = 0; j <= i; ++j) {
        int v = t[i][j];
        dp[i][j] = min(v + dp[i + 1][j], v + dp[i + 1][j + 1]);
      }
    }
    return dp[0][0];
  }
};

}  // namespace bottomUp

namespace topDown {

class Solution {
 public:
  int minimumTotal(vector<vector<int>>& triangle) {
    vector<vector<int>> dp(201, vector<int>(201, INT_MIN));
    function<int(int, int)> f = [&](int i, int j) {
      if (dp[i][j] != INT_MIN) return dp[i][j];
      if (i == triangle.size()) return dp[i][j] = 0;
      int v = triangle[i][j];
      return dp[i][j] = min(v + f(i + 1, j), v + f(i + 1, j + 1));
    };
    return f(0, 0);
  }
};

}  // namespace topDown
