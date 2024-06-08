#include <bits/stdc++.h>
using namespace std;

// https://leetcode.com/problems/longest-palindromic-substring/submissions/

// I've been solving this problem throughout the whole day in the bus, on my way
// to the summer party of the company I work for. On my way to red cross, when I
// wasn't writing, I was thinking about it and the pattern relationship between
// numbers.

// I continued to solve this problem next day exploring various ways to
// transform the state. I continued to explore various possibilities of how to
// store values in the state, how to reduce the computations, etc... I figured
// out at least 6 ways to store values in the state and compute the various new
// states. For every solution I looked for alternative solutions. I thought
// about the problem, values, numbers, relationships between numbers, etc...

namespace a {

class Solution {
 public:
  string longestPalindrome(string s) {
    int longest = 0;
    int start = -1, end = -1;
    for (int i = s.length() - 1; i >= 0; --i) {
      int l = 0, r = i;
      while (r <= s.length() - 1) {
        bool isPalindrome = true;
        int o = l, k = r;
        while (o < k) {
          if (s[o] != s[k]) isPalindrome = false;
          ++o;
          --k;
        }
        if (isPalindrome && longest < r - l + 1) {
          longest = r - l + 1;
          start = l;
          end = r;
        }
        ++l;
        ++r;
      }
    }
    return s.substr(start, end - start + 1);
  }
};

}  // namespace a

namespace b {
class Solution {
 public:
  string longestPalindrome(string s) {
    vector<vector<int>> dp(s.length(), vector<int>(s.length(), -1));
    int longest = 0;
    int start = -1, end = -1;
    int invalid = numeric_limits<int>::min();
    for (int i = s.length() - 1; i >= 0; --i) {
      int l = 0, r = i;
      while (r <= s.length() - 1) {
        int dist = floor((r - l) / 2);
        int o = l + dist, k = r - dist;

        if (dp[o][k] == -1) {
          if (s[o] == s[k]) {
            dp[o][k] = k - o + 1;
            if (longest < dp[o][k]) {
              longest = dp[o][k];
              start = o;
              end = k;
            }
          } else {
            dp[o][k] = invalid;
          }
          --o;
          ++k;
        }

        while (o >= l && k <= r) {
          if (dp[o + 1][k - 1] != invalid && s[o] == s[k]) {
            dp[o][k] = k - o + 1;
            if (longest < dp[o][k]) {
              longest = dp[o][k];
              start = o;
              end = k;
            }
          } else {
            dp[o][k] = invalid;
          }
          --o;
          ++k;
        }

        ++l;
        ++r;
      }
    }
    return s.substr(start, end - start + 1);
  }
};

}  // namespace b

namespace c {

class Solution {
 public:
  string longestPalindrome(string s) {
    vector<vector<int>> dp(s.length(), vector<int>(s.length(), -1));
    int longest = 0;
    int start = -1, end = -1;
    int invalid = numeric_limits<int>::min();
    for (int i = s.length() - 1; i >= 0; --i) {
      int l = 0, r = i;
      while (r <= s.length() - 1) {
        int dist = floor((r - l) / 2);
        int o = l + dist, k = r - dist;

        if (dp[o][k] == -1) {
          while (o >= l && k <= r) {
            if (o == k) {
              dp[o][k] = 1;
              if (longest < dp[o][k]) {
                longest = dp[o][k];
                start = o;
                end = k;
              }
            } else {
              if (s[o] == s[k] && dp[o + 1][k - 1] != invalid) {
                int len = k - o == 1 ? 2 : dp[o + 1][k - 1] + 2;
                dp[o][k] = len;
                if (longest < dp[o][k]) {
                  longest = dp[o][k];
                  start = o;
                  end = k;
                }
              } else {
                dp[o][k] = invalid;
              }
            }
            --o;
            ++k;
          }
        }

        ++l;
        ++r;
      }
    }
    return s.substr(start, end - start + 1);
  }
};

}  // namespace c
