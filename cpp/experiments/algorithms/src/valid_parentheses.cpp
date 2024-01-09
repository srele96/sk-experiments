#include <bits/stdc++.h>
using namespace std;

// https://leetcode.com/problems/valid-parentheses

namespace a {

class Solution {
 public:
  bool hasMatchingOpening(const char opening, const char closing) {
    bool m1 = opening == '(' && closing == ')';
    bool m2 = opening == '[' && closing == ']';
    bool m3 = opening == '{' && closing == '}';
    return m1 || m2 || m3;
  }

  bool isValid(string s) {
    stack<char> stq;

    for (const char c : s) {
      if (c == '(' || c == '[' || c == '{') {
        stq.push(c);
      } else {
        // Stack is empty if the only character is the closing bracket
        if (stq.size() > 0 && hasMatchingOpening(stq.top(), c)) {
          stq.pop();
        } else {
          return false;
        }
      }
    }

    // Stack is empty if every opening has a closing
    return stq.size() == 0;
  }
};

}  // namespace a

namespace b {

class Solution {
 public:
  bool isValid(string s) {
    stack<char> stq;
    map<char, char> opening{{'}', '{'}, {']', '['}, {')', '('}};

    for (const char c : s) {
      if (c == '(' || c == '[' || c == '{') {
        stq.push(c);
      } else {
        // Stack is empty if the only character is the closing bracket
        // Check if the current closing paired to its opening is the same as
        //   stack opening
        if (stq.size() > 0 && opening[c] == stq.top()) {
          stq.pop();
        } else {
          return false;
        }
      }
    }

    // Stack is empty if every opening has a closing
    return stq.size() == 0;
  }
};

}  // namespace b

namespace c {

class Solution {
 public:
  bool isValid(string s) {
    stack<char> stq;
    map<char, char> opening{{'}', '{'}, {']', '['}, {')', '('}};
    bool isBalanced{true};

    function<void(int)> rec{[&](int i) {
      if (i < s.size()) {
        if (s[i] == '(' || s[i] == '[' || s[i] == '{') {
          stq.push(s[i]);
        } else {
          cout << stq.size() << "\n";
          if (stq.size() > 0 && opening[s[i]] == stq.top()) {
            stq.pop();
          } else {
            isBalanced = false;
          }
        }
        rec(i + 1);
      }
    }};

    rec(0);

    // Good luck understanding why this occurs!
    //
    // Recursion does not terminate when string is not balanced. Both the flag
    // and the size are indicators that the string is balanced.
    return isBalanced && stq.size() == 0;
  }
};

}  // namespace c
