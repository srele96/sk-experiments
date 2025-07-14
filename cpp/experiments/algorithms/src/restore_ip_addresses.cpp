#include "bits/stdc++.h>"
using namespace std;

// Uses ideas from:
// https://leetcode.com/problems/palindrome-partitioning/description/?envType=problem-list-v2&envId=dynamic-programming
// https://leetcode.com/problems/word-break-ii/description/
// https://leetcode.com/problems/word-break/description/?envType=problem-list-v2&envId=dynamic-programming

namespace bottomUp_howDoesItEvenWork {

// Oddly, i only figured this would work for up to s.size() == 12 4x3 addresses
// However... Nope.
// Maybe... Since up to 12, we had already built the addresses...
// Yeah, i can't imagine how it would work
// Because:

/*
1
1 2
  2 // builds base starting at 2
1 2 3
  2 3
    3 // builds base starting at 3
1 2 3 4 // > 3 digits
  2 3 4
    3 4
      4 // builds base starting at 4
1 2 3 4 5 // > 3 digits
  2 3 4 5 // > 3 digits
    3 4 5
      4 5
        5
1 2 3 4 5 6
  2 3 4 5 6
    3 4 5 6
      4 5 6
        5 6
          6
*/
// Ok, looks good
// Looking at these, the dp would have base starting at each position
// Thanks to dp build-up approach

class Solution {
 public:
  vector<string> restoreIpAddresses(string s) {
    vector<vector<string>> dp(s.size() + 1);
    dp[0] = {""};
    for (int i = 1; i <= s.size(); ++i) {
      int j = i - 3 < 0 ? 0 : i - 3;
      for (; j < i; ++j) {
        const string str = s.substr(j, i - j);
        if (str.size() <= 3) {
          int v = stoi(str);
          bool strLeadZero = str.size() > 1 && str[0] == '0';
          if (!strLeadZero && v <= 255) {
            for (const string prev : dp[j]) {
              int dots = 0;
              for (const char c : prev) {
                if (c == '.') ++dots;
              }
              if (dots < 3) {
                if (prev == "") {
                  dp[i].emplace_back(str);
                } else {
                  dp[i].emplace_back(prev + "." + str);
                }
              }
            }
          }
        }
      }
    }
    vector<string> r;
    for (const string& str : dp[s.size()]) {
      int dots = 0;
      for (const char c : str) {
        if (c == '.') ++dots;
      }
      if (dots == 3) r.emplace_back(str);
    }
    return r;
  }
};

}  // namespace bottomUp_howDoesItEvenWork

namespace skeleton {

class Solution {
 public:
  vector<string> restoreIpAddresses(string s) {
    vector<vector<vector<string>>> dp(s.size() + 1);
    dp[0] = {{""}};
    for (int i = 1; i <= s.size(); ++i) {
      for (int j = 0; j < i; ++j) {
        const string str = s.substr(j, i - j);
        if (str.size() <= 3) {
          int v = stoi(str);
          bool strLeadZero = str.size() > 1 && str[0] == '0';
          if (!strLeadZero && v <= 255) {
            for (vector<string> prev : dp[j]) {
              if (prev.size() < 4) {
                const string last = prev[prev.size() - 1];
                if (last == "") {
                  dp[i].push_back({str});
                } else {
                  prev.emplace_back(str);
                  dp[i].emplace_back(prev);
                }
                // cout << last << "." << str << "\n";
              }
            }
          }
        }
      }
    }
    for (const vector<string>& r : dp[s.size()]) {
      if (r.size() == 4) {
        for (const string& str : r) {
          cout << str << ".";
        }
        cout << "\n";
      }
    }

    return {};
  }
};

}  // namespace skeleton
