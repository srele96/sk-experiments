#include <cmath>
#include <limits>
#include <string>
#include <vector>
using namespace std;

// the idea was to use max sum of prefix at postfix at every split string and we
// get the prefix and postfix sum using two arrays

// https://leetcode.com/problems/maximum-score-after-splitting-a-string/

class Solution {
 public:
  int maxScore(string s) {
    int n = s.length();
    vector<int> prefix(n);
    vector<int> postfix(n);
    prefix[0] = s[0] == '0' ? 1 : 0;
    for (int i = 1; i < n; ++i) {
      prefix[i] = prefix[i - 1] + (s[i] == '0' ? 1 : 0);
    }
    postfix[n - 1] = s[n - 1] == '1' ? 1 : 0;
    for (int i = n - 2; i >= 0; --i) {
      postfix[i] = postfix[i + 1] + (s[i] == '1' ? 1 : 0);
    }
    int result = numeric_limits<int>::min();
    for (int i = 0; i < n - 1; ++i) {  // to n - 1 cus two non empty strings
      result = max(result, prefix[i] + postfix[i + 1]);
    }
    return result;
  }
};
