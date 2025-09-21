#include <bits/stdc++.h>
using namespace std;

namespace bottomUp {

class Solution {
 public:
  // What? Uses the same method, bottom-up, and beats 100% according to lc?
  vector<string> wordBreak(string s, vector<string>& wd) {
    unordered_set<string> d{wd.begin(), wd.end()};
    vector<vector<string>> dp(s.size() + 1);
    dp[0] = {""};
    for (int i = 1; i <= s.size(); ++i) {
      for (int j = 0; j < i; ++j) {
        const string str = s.substr(j, i - j);
        if (d.count(str)) {
          for (const string p : dp[j]) {
            const string sep = p.size() == 0 ? "" : " ";
            dp[i].emplace_back(p + sep + str);
          }
        }
      }
    }
    return dp[s.size()];
  }
};

}  // namespace bottomUp

namespace topDownOptionalMemoItem {

class Solution {
 public:
  vector<string> wordBreak(string s, vector<string>& wd) {
    unordered_set<string> d{wd.begin(), wd.end()};
    vector<optional<vector<string>>> dp(s.size() + 1);
    function<vector<string>(int)> f{[&](int i) -> vector<string> {
      if (dp[i]) return *dp[i];
      if (i == 0) return *(dp[i] = {""});
      vector<string> r;
      for (int j = 0; j < i; ++j) {
        vector<string> prev = f(j);
        string str = s.substr(j, i - j);
        if (d.count(str)) {
          for (const string& p : prev) {
            const string sep = p.size() > 0 ? " " : "";
            r.emplace_back(p + sep + str);
          }
        }
      }
      return *(dp[i] = r);
    }};

    return f(s.size());
  }
};

}  // namespace topDownOptionalMemoItem

namespace topDownIncorrectMemoization {

class Solution {
 public:
  vector<string> wordBreak(string s, vector<string>& wd) {
    unordered_set<string> d{wd.begin(), wd.end()};
    vector<vector<string>> dp(s.size() + 1);
    function<vector<string>(int)> f{[&](int i) -> vector<string> {
      if (dp[i].size() > 0) return dp[i];
      if (i == 0) return dp[i] = {""};
      vector<string> r;
      for (int j = 0; j < i; ++j) {
        vector<string> prev = f(j);
        string str = s.substr(j, i - j);
        if (d.count(str)) {
          for (const string& p : prev) {
            const string sep = p.size() > 0 ? " " : "";
            r.emplace_back(p + sep + str);
          }
        }
      }
      return dp[i] = r;
    }};

    return f(s.size());
  }
};

}  // namespace topDownIncorrectMemoization
