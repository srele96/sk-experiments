#include <bits/stdc++.h>
using namespace std;

namespace gotHelpByGptMemorizedMostOfTheAlgorithm {

// The idea of a stack is to keep track of increasing heights
//
// As soon as we encounter a height drop, we keep removing heights from the
// stack which are taller than the current height.
// The reason behind that is, the new height limits the maximal rectangle area
// Increasing width and height both contribute to maximal area.

class Solution {
 public:
  constexpr static int L = 200;
  int heights[L];
  int maximalRectangle(vector<vector<char>>& mat) {
    memset(heights, 0, sizeof(heights));
    int n = mat.size(), m = mat[0].size();
    stack<int> s;
    int r = 0;
    for (int i = 0; i < n; ++i) {
      while (!s.empty()) s.pop();
      for (int j = 0; j < m; ++j) {
        if (mat[i][j] == '1')
          ++heights[j];
        else
          heights[j] = 0;

        while (!s.empty() && heights[j] < heights[s.top()]) {
          int l = s.top();
          s.pop();
          int width = s.empty() ? j : j - s.top() - 1;
          int a = heights[l] * width;
          r = max(r, a);
          // cout << a << ", ";
        }
        s.push(j);
        // cout << "\n";
      }
      while (!s.empty()) {
        int l = s.top();
        s.pop();
        int width = s.empty() ? m : m - s.top() - 1;
        int a = width * heights[l];
        r = max(r, a);
        // cout << a << ", ";
      }
      // cout << "\n";
    }
    return r;
  }
};

}  // namespace gotHelpByGptMemorizedMostOfTheAlgorithm
