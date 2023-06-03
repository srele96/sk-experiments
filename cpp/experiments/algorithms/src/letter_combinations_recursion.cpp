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
  vector<string> result;
  if (digits.length() == 0) {
    return result;
  } else if (digits.length() == 1) {
    const string key{digits[0]};
    for (const string& letter : keyboard[key]) {
      result.push_back(letter);
    }
  } else {
    const string key{digits[0]};
    const vector<string> combinations{solve(digits.substr(1))};
    for (const string& letter : keyboard[key]) {
      for (const string& combination : combinations) {
        result.push_back(letter + combination);
      }
    }
  }

  return result;
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
