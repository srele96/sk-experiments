#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  static constexpr int L = 20;
  vector<int> dp[L][L];
  vector<string> tokens;
  vector<int> solve(int i, int j) {
    if (dp[i][j].size() > 0) return dp[i][j];
    if (i == j) return dp[i][j] = {stoi(tokens[i])};
    vector<int> r;
    for (int m = i; m < j; m += 2) {
      const string op = tokens[m + 1];
      for (const int a : solve(i, m)) {
        for (const int b : solve(m + 2, j)) {
          if (op == "*") r.push_back(a * b);
          if (op == "-") r.push_back(a - b);
          if (op == "+") r.push_back(a + b);
        }
      }
    }
    return dp[i][j] = r;
  }
  vector<int> diffWaysToCompute(string expression) {
    for (int i = 0; i < L; ++i) {
      for (int j = 0; j < L; ++j) {
        dp[i][j] = {};
      }
    }
    string num;
    for (const char c : expression) {
      if (c == '*' || c == '-' || c == '+') {
        tokens.push_back(num);
        tokens.push_back(string{c});
        num = "";
        continue;
      }
      num.push_back(c);
    }
    tokens.push_back(num);
    for (const string& token : tokens) cout << token << ", ";

    return solve(0, tokens.size() - 1);
  }
};
