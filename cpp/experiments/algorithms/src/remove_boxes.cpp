#include <bits/stdc++.h>
using namespace std;

namespace solvedByChatGptMemorizedByMe {

class Solution {
 public:
  vector<int> b;
  constexpr static int L = 100;
  int dp[L][L][L];

  int _removeBoxes(int i, int j, int k) {
    if (i > j) return 0;
    if (dp[i][j][k] != -1) return dp[i][j][k];

    int r = pow(k + 1, 2) + _removeBoxes(i + 1, j, 0);
    for (int m = i + 1; m <= j; ++m) {
      if (b[m] == b[i]) {
        r = max(r, _removeBoxes(i + 1, m - 1, 0) + _removeBoxes(m, j, k + 1));
      }
    }
    return dp[i][j][k] = r;
  }

  int removeBoxes(vector<int>& boxes) {
    b = move(boxes);
    memset(dp, -1, sizeof(dp));
    return _removeBoxes(0, b.size() - 1, 0);
  }
};

}  // namespace solvedByChatGptMemorizedByMe

namespace tle {

class Solution {
 public:
  unordered_map<int, unordered_map<int, unordered_map<string, int>>> dp;
  int solve(int i, int k, const string& b) {
    if (dp.count(i) && dp[i].count(k) && dp[i][k].count(b)) {
      return dp[i][k][b];
    }
    if (b.size() == 0) return dp[i][k][b] = k;
    int r = 0;
    for (int idx = 0; idx < b.size(); ++idx) {
      int el = idx, curK = 0;
      char val = b[el];
      while (el < b.size() && b[el] == val) {
        ++curK;
        ++el;
      }
      r = max(r, solve(0, k + curK * curK,
                       b.substr(0, idx) + b.substr(el, b.size() - el)));
    }
    return dp[i][k][b] = r;
  }

  int removeBoxes(vector<int>& boxes) {
    string b;
    for (const int v : boxes) {
      b.push_back(v + '0');
    }
    return solve(0, 0, b);
  }
};

}  // namespace tle
