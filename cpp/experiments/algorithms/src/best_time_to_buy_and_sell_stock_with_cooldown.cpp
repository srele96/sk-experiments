#include <bits/stdc++.h>
using namespace std;

/*
I don't know... hae i ever done stocks problem... using bottom-up... ?
I certail don't feel like i did... :D

However, this problem feels like almost exactly the same variation of being able
to hold up to k stocks...

So i knew solution immediately...
*/
class Solution {
 public:
  vector<int> p;
  static constexpr int L = 5000, W = 2;
  bool vis[L][W][W] = {};
  int dp[L][W][W] = {};

  int solve(int i, bool cooldown, bool holding) {
    if (i >= p.size()) return 0;
    if (vis[i][cooldown][holding]) {
      return dp[i][cooldown][holding];
    }
    vis[i][cooldown][holding] = true;
    if (cooldown) {
      return dp[i][cooldown][holding] = solve(i + 1, false, holding);
    }
    if (holding) {
      int sell = solve(i + 1, true, false) + p[i];
      int skip = solve(i + 1, cooldown, holding);
      return dp[i][cooldown][holding] = max(sell, skip);
    }
    int buy = solve(i + 1, cooldown, true) - p[i];
    int skip = solve(i + 1, cooldown, holding);
    return dp[i][cooldown][holding] = max(buy, skip);
  }
  int maxProfit(vector<int>& prices) {
    p = move(prices);
    return solve(0, false, false);
  }
};
