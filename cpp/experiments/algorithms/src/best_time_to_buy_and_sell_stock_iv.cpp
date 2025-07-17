#include <bits/stdc++.h>
using namespace std;

namespace topDown {

static int dp[1001][101][101][2];

class Solution {
 public:
  vector<int> p;
  int n = 0;

  int solve(int i, int sell, int buy, int h) {
    if (dp[i][sell][buy][h] != INT_MIN) return dp[i][sell][buy][h];

    if (i > n) return 0;

    int hold = solve(i + 1, sell, buy, h);
    int act = INT_MIN;

    if (h) {
      if (sell > 0) {
        act = solve(i + 1, sell - 1, buy, false) + p[i];
      }
    } else {
      if (buy > 0) {
        act = solve(i + 1, sell, buy - 1, true) - p[i];
      }
    }

    return dp[i][sell][buy][h] = max(hold, act);
  }

  int maxProfit(int k, vector<int>& prices) {
    n = prices.size() - 1;
    p = move(prices);

    for (int i = 0; i < 1001; ++i)
      for (int j = 0; j < 101; ++j)
        for (int m = 0; m < 101; ++m)
          for (int l = 0; l < 2; ++l) dp[i][j][m][l] = INT_MIN;

    return solve(0, k, k, false);
  }
};

}  // namespace topDown
