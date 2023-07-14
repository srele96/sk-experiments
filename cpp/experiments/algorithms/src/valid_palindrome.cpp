#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  bool isPalindrome(string s) {
    string strp{""};
    for (auto& c : s) {  // Take reference to each character.
      if (isalnum(c)) strp += move(tolower(c));  // Consume it, faster runtime.
    }
    int l = 0, r = strp.length() - 1;
    while (l < r) {
      if (strp[l] != strp[r]) return false;
      ++l;
      --r;
    }
    return true;
  }
};

int main() {
  string s{"0P"};
  cout << Solution{}.isPalindrome(s);
}
