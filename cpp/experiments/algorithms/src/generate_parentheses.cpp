#include <bits/stdc++.h>
using namespace std;

namespace bottomUpDP {

class Solution {
 public:
  vector<string> generateParenthesis(int n) {
    vector<vector<tuple<string, int, int>>> dp(n * 2 + 1);
    vector<string> r;
    dp[0] = {{"", 0, n}};
    for (int i = 1; i <= n * 2; ++i) {
      for (const auto& [s, o, p] : dp[i - 1]) {
        if (o < p) {
          dp[i].emplace_back(s + "(", o + 1, p);
          if (i == n * 2) {
            r.emplace_back(s + "(");
          }
        }
        if (o > 0) {
          dp[i].emplace_back(s + ")", o - 1, p - 1);
          if (i == n * 2) {
            r.emplace_back(s + ")");
          }
        }
      }
    }
    return r;
  }
};

/*
"("
  "()"
      "()("
            "()()"
            "()(("
  "(("
      "((("
            "(((("
            "((()"
      "(()"
            ""
*/

}  // namespace bottomUpDP

namespace iterativeBacktrackingYay {

// Yay... mostly my solution... the GPT told me to use tuple...
// I already knew everything else, how to do...
// Just push states on a stack... and expect them to run... Yay... Nay... Way...
class Solution {
 public:
  vector<string> generateParenthesis(int n) {
    stack<tuple<string, int, int>> stk;
    stk.emplace("", 0, n);
    vector<string> r;
    while (!stk.empty()) {
      auto [s, o, p] = stk.top();
      stk.pop();
      if (o == 0 && p == 0) {
        r.emplace_back(s);
      }
      if (o < p) {
        stk.emplace(s + "(", o + 1, p);
      }
      if (o > 0) {
        stk.emplace(s + ")", o - 1, p - 1);
      }
    }
    return r;
  }
};

}  // namespace iterativeBacktrackingYay

namespace quiteFasterSolution {

// Quite a bit faster solution...
class Solution {
 public:
  vector<string> r;
  string s;
  void f(int o, int p) {
    if (o == 0 && p == 0) {
      r.emplace_back(s);
      return;
    }
    if (o < p) {
      s.push_back('(');
      f(o + 1, p);
      s.pop_back();
    }
    if (o > 0) {
      s.push_back(')');
      f(o - 1, p - 1);
      s.pop_back();
    }
  }
  vector<string> generateParenthesis(int n) {
    f(0, n);
    return r;
  }
};

}  // namespace quiteFasterSolution

namespace somewhatFasterVersion {

// Somewhat faster version
class Solution {
 public:
  vector<string> r;
  void f(int o, int p, const string& s) {
    if (o == 0 && p == 0) {
      r.emplace_back(s);
      return;
    }
    if (o < p) {
      f(o + 1, p, s + "(");
    }
    if (o > 0) {
      f(o - 1, p - 1, s + ")");
    }
  }
  vector<string> generateParenthesis(int n) {
    f(0, n, "");
    return r;
  }
};

}  // namespace somewhatFasterVersion

namespace initialSolution {

class Solution {
 public:
  vector<string> generateParenthesis(int n) {
    function<vector<string>(int, int, string)> f =
        [&](int o, int p, string s) -> vector<string> {
      if (o == 0 && p == 0) {
        // cout << o << ", " << p << ", " << s << "\n";
        return {s};
      }
      vector<string> r;
      if (o < p) {
        auto a = f(o + 1, p, s + "(");
        r.insert(r.end(), a.begin(), a.end());
      }
      if (o > 0) {
        auto b = f(o - 1, p - 1, s + ")");
        r.insert(r.end(), b.begin(), b.end());
      }
      return r;
    };
    return f(0, n, "");
  }
};

/*

"", 0, 2
         "(", 1, 2
                    "((", 2, 2
                              "(()", 1, 1
                                          "(())", 0, 0
                    "()", 0, 1
                              "()(", 1, 1
                                        "()()", 0, 0

"", 0, 2
         "(", 1, 2
                   "()", 0, 1
                              "()(", 1, 1
                                          "()()", 0, 0
                   "((", 2, 2
                              "(()", 1, 1
                                          "(())", 0, 0

"", 0, 3
         "(", 1, 3
                   "()", 0, 2
                             "()(", 1, 2
                   "((", 2, 3
                             "(()", 1, 2
                                         "(()(", 2, 2
                                                      "(()()", 1, 1
                                                                     "(()())",
0, 0
                                         "(())", 0, 1
                                                      "(())(", 1, 1
                                                                    "(())()", 0,
0
                             "(((", 3, 3
                                         "((()", 2, 2
                                                      "((())", 1, 1
                                                                    "((()))", 0,
0

""
  ()
    ()()
        ()()()
              ()()()()
              ()()()()
              (()()())
        (()())
              (()())()
              ()(()())
              ((()()))
    (())
        (())()
        ()(())
        ((()))
*/

}  // namespace initialSolution

class Solution {
 private:
  void backtrack(vector<string>* result, vector<string> comb, int n,
                 int left = 0, int right = 0) {
    if (static_cast<int>(comb.size()) == 2 * n) {
      string s_comb{
          accumulate(comb.begin(), comb.end(), string(),
                     [](const string& a, const string& b) { return a + b; })};

      result->push_back(s_comb);
      return;
    }
    if (left < n) {
      comb.push_back("(");
      backtrack(result, comb, n, left + 1, right);
      comb.pop_back();
    }
    if (right < left) {
      comb.push_back(")");
      backtrack(result, comb, n, left, right + 1);
      comb.pop_back();
    }
  }

 public:
  vector<string> generateParenthesis(int n) {
    vector<string> result;
    backtrack(&result, {}, n);
    return result;
  }
};

int main() {
  vector<int> ns{1, 2, 3, 4};
  for (const int n : ns) {
    cout << "For n = " << n << "\n";
    for (const string& s : Solution{}.generateParenthesis(n)) {
      cout << s << "\n";
    }
    cout << "\n";
  }
}
