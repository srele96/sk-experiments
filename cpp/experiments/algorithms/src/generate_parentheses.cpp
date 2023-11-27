#include <bits/stdc++.h>
using namespace std;

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
