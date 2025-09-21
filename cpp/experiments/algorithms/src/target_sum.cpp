#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<int> n;
  array<unordered_map<int, int>, 21> dp;
  /*
  int solve(const int i, const int s = 0) {
    if (i >= n.size()) return s == t ? 1 : 0;
    return solve(i + 1, n[i] + s) + solve(i + 1, -n[i] + s);
  }
  */
  int solve(const int i, const int s) {
    if (i < 0) return s == 0 ? 1 : 0;
    if (dp[i].count(s)) return dp[i][s];
    return dp[i][s] = solve(i - 1, s - n[i]) + solve(i - 1, s + n[i]);
  }
  int itr(const int t) {
    array<unordered_map<int, int>, 21> dp;
    if (n[0] == 0)
      dp[0][0] = 2;
    else {
      dp[0][-n[0]] = 1;
      dp[0][n[0]] = 1;
    }
    for (int i = 1; i < n.size(); ++i) {
      for (const auto& p : dp[i - 1]) {
        dp[i][p.first - n[i]] += p.second;
        dp[i][p.first + n[i]] += p.second;
      }
    }
    return dp[n.size() - 1][t];
  }
  /*
    int iter(const int t) {
    array<vector<int>, 21> dp;
    dp[0].emplace_back(-n[0]);
    dp[0].emplace_back(n[0]);
    for(int i = 1; i < n.size(); ++i) {
      for(const auto s : dp[i - 1]) {
        dp[i].emplace_back(s - n[i]);
        dp[i].emplace_back(s + n[i]);
      }
    }
    int r = 0;
    for(const int s : dp[n.size() - 1]) if (s == t) ++r;
    return r;
  }
  */
  int findTargetSumWays(vector<int>& nums, int target) {
    n = move(nums);
    // return solve(n.size() - 1, target);
    return itr(target);
  }
};

/*

0, -1 -> 1
0, 1 -> 1
  1, 0 -> 1
  1, -2 -> 1
  1, 2 -> 1
  1, 0 -> 2
    2, 1 -> 1
    2, -1 -> 1
    2, -1 -> 2
    2, -3 ->
    2, 3
    2, 1
    2, 1
    2, -1
0, 2
0, 4
  1, 3
  1, 1
  1, 5
  1, 3
    2, 4
    2, 2
    2, 2
    2, 0
    2, 6
    2, 4
    2, 4
    2, 2
      3, 5
      3, 3
      3, 3
      3, 1
      3, 3
      3, 1
*/

/*
1,1,1,1,1

0, 0
  1, 1
    2, 2
      3, 3
        4, 4
          5, 5
          5, 3
        4, 2
          5, 3
          5, 1
      3, 1
        4, 2
          5, 3
        4, 0
          5, -1
    2, 0
      3, 1
        4, 2
          5, 3
        4, 0
          5, -1
      3, -1
        4, 0
          5, 1
        4, -2
          5, -3
  1, -1
    2, 0
    2, -2

0, 0
  1, 1 -> 4
    2, 2 -> 3
      3, 3 -> 2
        4, 4 -> 1
          5, 5 -> 0
          5, 3 -> 1
        4, 2 -> 1
          5, 3 -> 1
          5, 1 -> 0
      3, 1 -> 1
        4, 2 -> 1
          5, 3 -> 1
          5, 1 -> 0
        4, 0 -> 0
          5, 1 -> 0
          5, -1 -> 0
    2, 0 -> 1
      3, 1 -> 1
        4, 2 -> 1
          5, 3 -> 1
          5, 1 -> 0
        4, 0 -> 0
          5, 1 -> 0
          5, -1 -> 0
      3, -1 -> 0
        4, 0 -> 0
          5, 1 -> 0
          5, -1 -> 0
        4, -2 -> 0
          5, -1 -> 0
          5, -3 -> 0
  1, -1
    2, 0
      3, 1
        4, 2
          5, 3
          5, 1
        4, 0
          5, 1
          5, -1
      3, -1
        4, 0
          5, 1
          5, -1
        4, -2
          5, -1
          5, -3
    2, -2
      3, -1
        4, 0
          5, 1
          5, -1
        4, -2
          5, -1
          5, -3
      3, -3
        4, -2
          5, -1
          5, -3
        4, -4
          5, -3
          5, -5
*/
// return sum
// count returned sums
// exit
