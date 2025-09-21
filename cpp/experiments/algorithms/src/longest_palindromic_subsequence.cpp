#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  string s;
  static constexpr int L = 1001;
  int dp[L][L];
  int vis[L][L];
  // vector<string> solve(int i, int j) {
  //   if (i > j) return {""};
  //   if (i == j) return {s.substr(i, 1)};
  //   vector<string> r;
  //   if (s[i] == s[j]) {
  //     for(const auto& str : solve(i + 1, j - 1)) {
  //       r.emplace_back(s[i] + str + s[j]);
  //     }
  //   }
  //   const auto right = solve(i + 1, j);
  //   r.insert(r.end(), right.begin(), right.end());
  //   const auto left = solve(i, j - 1);
  //   r.insert(r.end(), left.begin(), left.end());
  //   return r;
  // }
  int solve(int i, int j) {
    if (vis[i][j]) return dp[i][j];
    vis[i][j] = true;
    if (i > j) return dp[i][j] = 0;
    if (i == j) return dp[i][j] = 1;
    if (s[i] == s[j]) return dp[i][j] = 2 + solve(i + 1, j - 1);
    return dp[i][j] = max(solve(i + 1, j), solve(i, j - 1));
  }
  int longestPalindromeSubseq(string str) {
    s = move(str);
    memset(vis, 0, sizeof(vis));

    return solve(0, s.size() - 1);
  }
};
