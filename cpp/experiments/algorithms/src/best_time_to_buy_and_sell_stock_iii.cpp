#include <bits/stdc++.h>
using namespace std;

namespace topDownNoTLE {

int f(int i, int t, bool h, int dp[100001][3][2], vector<int>& p) {
  if (dp[i][t][h] != INT_MIN) return dp[i][t][h];
  if (i == p.size() || t == 0) return dp[i][t][h] = 0;
  int hold = f(i + 1, t, h, dp, p);
  int act = 0;
  if (h) {
    act = f(i + 1, t - 1, false, dp, p) + p[i];
  } else {
    act = f(i + 1, t, true, dp, p) - p[i];
  }
  return dp[i][t][h] = max(hold, act);
}

class Solution {
 public:
  int maxProfit(vector<int>& p) {
    static int dp[100001][3][2];
    for (int i = 0; i < 100001; ++i) {
      for (int j = 0; j < 3; ++j) {
        for (int k = 0; k < 2; ++k) {
          dp[i][j][k] = INT_MIN;
        }
      }
    }

    return f(0, 2, false, dp, p);
  }
};

}  // namespace topDownNoTLE

namespace TLE {

class Solution {
 public:
  int maxProfit(vector<int>& p) {
    vector<unordered_map<int, unordered_map<bool, unordered_map<int, int>>>> dp(
        p.size() + 1);
    function<int(int, int, bool, int)> f = [&](int i, int t, bool h, int s) {
      if (dp[i].count(t) && dp[i][t].count(h) && dp[i][t][h].count(s))
        return dp[i][t][h][s];
      if (i == p.size()) return dp[i][t][h][s] = s;
      if (t > 0) {
        int hold = f(i + 1, t, h, s);
        int act = s;
        if (h) {
          act = f(i + 1, t - 1, false, s + p[i]);
        } else {
          act = f(i + 1, t, true, s - p[i]);
        }
        return dp[i][t][h][s] = max(hold, act);
      }
      return dp[i][t][h][s] = s;
    };
    return f(0, 2, false, 0);
  }
};

}  // namespace TLE

/*

0, 2, false, 0
  1, 2, false, 0
    2, 2, false, 0
      3, 2, false, 0
      3, 1, true, -5
    2, 1, true, -3
  1, 1, true, -3

*/
