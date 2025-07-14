#include <bits/stdc++.h>
using namespace std;

// https://leetcode.com/problems/decode-ways/description/

// Based on segmentation algorithm
// Word Break
// Word Break II

class Solution {
 public:
  bool decodable(const string& s) {
    int v = stoi(s);
    if (s.size() == 2 && (v < 10 || v > 26)) return false;
    if (s.size() == 1 && v == 0) return false;
    return true;
  }
  int numDecodings(string s) {
    vector<int> dp(s.size() + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= s.size(); ++i) {
      for (int j = i - 2 < 0 ? 0 : i - 2; j < i; ++j) {
        if (decodable(s.substr(j, i - j))) {
          dp[i] += dp[j];
        }
      }
    }
    return dp[s.size()];
  }
};
