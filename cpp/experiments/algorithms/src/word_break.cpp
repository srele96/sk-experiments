#include <bits/stdc++.h>
using namespace std;

namespace claudeMemorizedSolution {

namespace topDown {

class Solution {
 public:
  bool wordBreak(string s, vector<string>& wd) {
    unordered_set<string> d{wd.begin(), wd.end()};
    vector<int> dp(s.size() + 1, -1);
    function<bool(int)> f{[&](int i) {
      if (dp[i] != -1) return dp[i];
      if (i == 0) return dp[i] = true;
      for (int j = 0; j < i; ++j) {
        if (f(j) && d.count(s.substr(j, i - j))) {
          return dp[i] = true;
        }
      }
      return dp[i] = false;
    }};
    return f(s.size());
  }
};

}  // namespace topDown

namespace bottomUp {

class Solution {
 public:
  bool wordBreak(string s, vector<string>& wordDict) {
    unordered_set<string> d{wordDict.begin(), wordDict.end()};
    vector<bool> dp(s.size());
    dp[0] = true;
    for (int i = 1; i <= s.size(); ++i) {
      for (int j = 0; j < i; ++j) {
        if (dp[j] && d.count(s.substr(j, i - j))) {
          dp[i] = true;
          break;
        }
      }
    }
    return dp[s.size()];
  }
};

}  // namespace bottomUp

}  // namespace claudeMemorizedSolution

namespace memory_limit_exceeded {

class Solution {
 public:
  vector<vector<vector<string>>> dp;

  Solution() : dp{vector<vector<vector<string>>>(300)} {}

  vector<vector<string>> partitions(const string& s, int i) {
    if (dp[i].size() > 0) return dp[i];
    if (i == 0) {
      return dp[i] = {{s.substr(i, 1)}};
    }
    vector<vector<string>> r;
    for (const vector<string>& row : partitions(s, i - 1)) {
      vector<string> a = row;
      a.push_back(s.substr(i, 1));
      r.push_back(a);
      vector<string> b = row;
      b[b.size() - 1] = b[b.size() - 1] + s.substr(i, 1);
      r.push_back(b);
    }
    return dp[i] = r;
  }
  bool wordBreak(string s, vector<string>& wordDict) {
    unordered_set<string> dict;
    for (const string& str : wordDict) {
      dict.insert(str);
    }
    vector<vector<string>> r = partitions(s, s.size() - 1);
    for (const vector<string>& row : r) {
      bool hasAll = true;
      for (const string& str : row) {
        if (!dict.contains(str)) {
          hasAll = false;
        }
      }
      if (hasAll) {
        return true;
      }
    }
    return false;
  }
};

}  // namespace memory_limit_exceeded
