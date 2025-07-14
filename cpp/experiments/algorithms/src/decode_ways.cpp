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

namespace suggestedByChatGpt {

// No idea how does it work. Save to analyze later.
// Supposedly is DP solution. Unlike others I've seen and am familiar with.

int numDecodings(string s) {
  int a = 1, b = s[0] != '0' ? 1 : 0;
  for (int i = 1; i < s.size(); ++i) {
    int c = 0;
    if (s[i] != '0') c += b;
    int x = (s[i - 1] - '0') * 10 + (s[i] - '0');
    if (x >= 10 && x <= 26) c += a;
    a = b;
    b = c;
  }
  return b;
}

}  // namespace suggestedByChatGpt
