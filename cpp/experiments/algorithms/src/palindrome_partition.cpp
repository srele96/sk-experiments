#include <bits/stdc++.h>
using namespace std;

namespace kindOfBacktrackingThroughParameterVector {

class Solution {
 public:
  vector<vector<string>> partition(string s) {
    function<bool(const string&)> pal = [&](const string& str) {
      int i = 0, j = str.length() - 1;
      while (i < j) {
        if (str.at(i) != str.at(j)) return false;
        ++i;
        --j;
      }
      return true;
    };
    function<bool(const vector<string>&)> allPal =
        [&](const vector<string>& strs) {
          bool r = true;
          for (auto str : strs) {
            if (!pal(str)) r = false;
          }
          return r;
        };
    function<vector<vector<string>>(vector<int>)> f = [&](vector<int> clips) {
      int start = clips.size() == 0 ? 0 : clips[clips.size() - 1];
      vector<vector<string>> r;
      for (int i = ++start; i < s.size(); ++i) {
        vector<int> cpy = clips;
        cpy.emplace_back(i);
        for (vector<string> strs : f(cpy)) {
          r.push_back(strs);
        }
      }

      vector<string> curr;
      int lpos = 0;
      for (int i : clips) {
        curr.emplace_back(s.substr(lpos, i - lpos));
        lpos = i;
      }
      curr.emplace_back(s.substr(lpos, s.size() - lpos));
      if (allPal(curr)) r.push_back(move(curr));

      return r;
    };

    return f({});
  }
};

}  // namespace kindOfBacktrackingThroughParameterVector

namespace bottomUpTabulationDP {

class Solution {
 public:
  vector<vector<string>> partition(string s) {
    function<bool(const string&)> pal = [](const string& str) {
      int i = 0, j = str.length() - 1;
      bool r = true;
      while (i < j) {
        if (str.at(i) != str.at(j)) r = false;
        ++i;
        --j;
      }
      return r;
    };
    function<bool(const vector<string>&)> allPal =
        [&](const vector<string>& arr) {
          bool r = true;
          for (const string& str : arr) {
            cout << str << "\n";
            if (!pal(str)) r = false;
          }
          return r;
        };

    vector<vector<vector<string>>> dp(s.size());
    dp[0].push_back({s.substr(0, 1)});
    for (int i = 1; i < dp.size(); ++i) {
      for (vector<string> arr : dp[i - 1]) {
        vector<string> a = arr;
        a[a.size() - 1] += s.substr(i, 1);
        if (i == dp.size() - 1) {
          if (allPal(a)) dp[i].emplace_back(a);
          ;
        } else {
          dp[i].emplace_back(a);
        }

        auto b = arr;
        b.emplace_back(s.substr(i, 1));
        if (i == dp.size() - 1) {
          if (allPal(b)) dp[i].emplace_back(b);
        } else {
          dp[i].emplace_back(b);
        }
      }
    }

    return dp[s.size() - 1];
  }
};
/*
dp = {

}
dp[0] = {{ 'a' }}
dp[1] = {{ 'a', 'b' }, { 'ab' }}
dp[2] = {{ 'a', 'b', 'c' }, { 'a', 'bc' }, { 'ab', 'c' }, { 'abc' }}

abcde
a
  a,b
      a,b,c
            a,b,c,d
                    a,b,c,d,e
                    a,b,c,de
            a,b,cd
                    a,b,cd,e
                    a,b,cde
      a,bc
            a,bc,d
                    a,bc,d,e
                    a,bc,de
            a,bcd
                    a,bcd,e
                    a,bcde
  ab
      ab,c
            ab,c,d
                    ab,c,d,e
                    ab,c,de
            ab,cd
                    ab,cd,e
                    ab,cde
      abc
            abc,d
                    abc,d,e
                    abc,de
            abcd
                    abcd,e
                    abcde

a
  ,b
      ,c
          ,d
              ,e
              e
          d
              ,e
              e
      c
          ,d
              ,e
              e
          d
              ,e
              e
  b
      ,c
          ,d
              ,e
              e
          d
              ,e
              e
      c
          ,d
              ,e
              e
          d
              ,e
              e

edcba

a
  b,
    c,
      ,d
        e,
        e
      d
        e,
        e
    c
      ,d
      d
  b

The algorithm is still quite slow...

Maybe the algorithm is slow exactly because of this...
Maybe it could be sped up?
By runing it from the right side of the string?

*/

}  // namespace bottomUpTabulationDP

namespace doesWhatIWantedButIDontUnderstandRequirementsCorrectly {

class Solution {
 public:
  vector<vector<string>> partition(string s) {
    function<bool(int, int)> isPalindrome = [&](int i, int j) {
      if (i > j) return true;
      return s.at(i - 1) == s.at(j - 1) && isPalindrome(i + 1, j - 1);
    };
    // vector<vector<int>> dp(s.size() + 1, vector<int>(s.size() + 1, -1));
    vector<vector<string>> r;
    function<void(int, int)> solve = [&](int i, int j) {
      if (i < 1 || j > s.size()) return;
      if (i > j) return;
      // if (dp[i][j] != -1) return;

      cout << i << ", " << j << "\n";
      if (isPalindrome(i, j)) {
        if (r.size() < (j - i + 1)) {
          r.resize(j - i + 1);
        }
        r[j - i].emplace_back(s.substr(i - 1, j - i + 1));
      }

      if (j > 0) solve(i, j - 1);
      if (i < j) solve(i + 1, j);
      // dp[i][j] = 1;
    };

    solve(1, s.size());

    return r;
  }
};

/*

1,4
    1,3
        1,2
            1,1
                0,1
                2,1
            2,2
        2,3
    2,4

*/

}  // namespace doesWhatIWantedButIDontUnderstandRequirementsCorrectly
