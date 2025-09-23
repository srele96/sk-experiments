// https://leetcode.com/problems/largest-plus-sign/description/

#include <bits/stdc++.h>
using namespace std;

namespace Fast {
// Once i understood that each direction does not depend on the other direction
// the variables `l, r, t, d` made sense because they are accumulators of length
// so far and encountering mat[a][b]=0 resets the length to 0

// I did not know how to use one for loop and 4 inside it, but once i started
// putting loops inside for(int i = 0; i < n; ++i) i understood that all loops
// follow the same pattern:

/*
for(int i = 0; i < n; ++i) {
  - left (column goes from start to end)
  for(int j = 0; j < n; ++j) {
    dp[i][j] = ...
  }
  - top (row goes from start to end)
  for(int j = 0; j < n; ++j) {
    dp[j][i] = ...
  }
  - right (column goes from end to start)
  for(int j = n - 1; j >= 0; --j) {
    dp[i][j] = ...
  }
  - down (row goes from end to start)
  for(int j = n - 1; j >= 0; --j) {
    dp[j][i] = ...
  }
}
*/

class Solution {
 public:
  int mat[501][501];
  int dp[501][501];
  int orderOfLargestPlusSign(int n, vector<vector<int>>& mines) {
    for (int i = 0; i < 501; ++i)
      for (int j = 0; j < 501; ++j) dp[i][j] = n + 1;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j) mat[i][j] = 1;
    for (const auto& v : mines) mat[v[0]][v[1]] = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0, r = 0; j < n; ++j) {
        dp[i][j] = min(dp[i][j], r = mat[i][j] == 0 ? 0 : r + 1);
      }
      for (int j = n - 1, l = 0; j >= 0; --j) {
        dp[i][j] = min(dp[i][j], l = mat[i][j] == 0 ? 0 : l + 1);
      }
      for (int j = 0, t = 0; j < n; ++j) {
        dp[j][i] = min(dp[j][i], t = mat[j][i] == 0 ? 0 : t + 1);
      }
      for (int j = n - 1, d = 0; j >= 0; --j) {
        dp[j][i] = min(dp[j][i], d = mat[j][i] == 0 ? 0 : d + 1);
      }
    }
    int r = 0;
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < n; ++j) r = max(r, dp[i][j]);
    return r;
  }
};

}  // namespace Fast

namespace Initial {

class Solution {
 public:
  int mat[501][501];
  int dp[501][501][4];
  int orderOfLargestPlusSign(int n, vector<vector<int>>& mines) {
    const int top = 0, down = 1, left = 2, right = 3;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        mat[i][j] = 1;
      }
    }
    for (const auto& mine : mines) {
      const int i = mine[0], j = mine[1];
      mat[i][j] = 0;
    }
    // Figure out how to use one ROW loop instead of 4
    // Then figure out how to use ONE state instead of 4
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (i == 0)
          dp[i][j][top] = 0;
        else {
          if (mat[i - 1][j] == 1) {
            dp[i][j][top] = dp[i - 1][j][top] + mat[i - 1][j];
          }
        }
      }
    }
    for (int i = n - 1; i >= 0; --i) {
      for (int j = 0; j < n; ++j) {
        if (i == n - 1)
          dp[i][j][down] = 0;
        else {
          if (mat[i + 1][j] == 1) {
            dp[i][j][down] = dp[i + 1][j][down] + mat[i + 1][j];
          }
        }
      }
    }
    for (int j = 0; j < n; ++j) {
      for (int i = 0; i < n; ++i) {
        if (j == 0)
          dp[i][j][left] = 0;
        else {
          if (mat[i][j - 1] == 1) {
            dp[i][j][left] = dp[i][j - 1][left] + mat[i][j - 1];
          }
        }
      }
    }
    for (int j = n - 1; j >= 0; --j) {
      for (int i = 0; i < n; ++i) {
        if (j == n - 1)
          dp[i][j][right] = 0;
        else {
          if (mat[i][j + 1] == 1) {
            dp[i][j][right] = dp[i][j + 1][right] + mat[i][j + 1];
          }
        }
      }
    }
    int r = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        if (mat[i][j] == 1) {
          r = max(r, min({dp[i][j][left], dp[i][j][right], dp[i][j][top],
                          dp[i][j][down]}) +
                         1);
        }
      }
    }
    return r;
  }
};

}  // namespace Initial
