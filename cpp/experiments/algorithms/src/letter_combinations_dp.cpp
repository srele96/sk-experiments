#include <bits/stdc++.h>
using namespace std;

unordered_map<string, vector<string>> keyboard{{"1", {}},
                                               {"2", {"a", "b", "c"}},
                                               {"3", {"d", "e", "f"}},
                                               {"4", {"g", "h", "i"}},
                                               {"5", {"j", "k", "l"}},
                                               {"6", {"m", "n", "o"}},
                                               {"7", {"p", "q", "r", "s"}},
                                               {"8", {"t", "u", "v"}},
                                               {"9", {"w", "x", "y", "z"}}};

vector<string> solve(const string& digits) {
  if (digits.length() < 1) return {};

  vector<vector<string>> dp(digits.length());
  string key{digits[digits.length() - 1]};
  for (const string& letter : keyboard[key])
    dp[digits.length() - 1].push_back(letter);

  if (digits.length() == 1) return dp[digits.length() - 1];

  for (int i{static_cast<int>(digits.length()) - 2}; i >= 0; --i) {
    const string digit{digits[i]};
    for (const string& letter : keyboard[digit]) {
      for (const string& combination : dp[i + 1]) {
        dp[i].push_back(letter + combination);
      }
    }
  }

  return dp[0];
}

int main() {
  int t;
  cin >> t;
  while (t--) {
    string number;
    cin >> number;
    for (const auto& combination : solve(number)) cout << combination << " ";
    cout << "\n";
  }

  return 0;
}
