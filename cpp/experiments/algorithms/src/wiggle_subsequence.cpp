#include <bits/stdc++.h>
using namespace std;

/*
to 2 we came fron any 2 + 1 ... n - 1
from 2 we go to any 0 ... 2 - 1

so a number 0 has been reached from any 0 + 1 ... n - 1

to,from
0 < 0 = 1

1 < 0 = 0,0 + 1,0
1 < 1 = 1

2 < 0 = 0,0 <
2 < 1
2 < 2 = 1

3 < 0
3 < 1
3 < 2
3 < 3

0,1 =
0,2
0,3
0,4

1,1
1,2
1,3
1,4

2,2
2,3
2,4

3,3
3,4

4,4

4,4
  0,4
    -1,0
  1,4
    0,1
      -1,0
  2,4
    0,2
      -1,0
    1,2
      0,1
        -1,0
  3,4
    0,3
      -1,0
    1,3
      0,1
        -1,0
    2,3
      0,2
        -1,0
      1,2
        0,1
          -1,0

0: 1
1: 1 or 2
2: 1, 2 or 3
3: 1, 2, 3, or 4

4,4
      0,4
                            -1,0
      1,4
                        0,1
                            -1,0
      2,4
                  0,2
                            -1,0
                  1,2
                        0,1
                            -1,0
      3,4
            0,3
                            -1,0
            1,3
                        0,1
                            -1,0
            2,3
                  0,2
                            -1,0
                  1,2
                        0,1
                            -1,0

[0][1] = 1 + [-1][0]

[0][2] = 1 + [-1][0]
[1][2] = 1 + [0][1]

[0][3]
        [-1][0]
[1][3]
        [0][1]
[2][3]
        [0][2]
        [1][2]

int len = 0;
for(int i = 1; i < n; ++i) {
  for(int j = 0; j < i; ++j) {
    for(int prevIdx = i; prevIdx < n; ++prevIdx) {
      int diff = nums[i] - nums[j];
      int prevDiff = nums[prevIdx] - nums[i];
      int diff = nums[i] - nums[j];
      dp[i][prevIdx] = max(dp[i][prevIdx], 1 + dp[j][i]);
    }
  }
}


*/

enum class SGN { POS, NEG, NONE };

SGN sgn(const int a) {
  if (a == 0) return SGN::NONE;
  return a > 0 ? SGN::POS : SGN::NEG;
}

class Solution {
 public:
  static constexpr int L = 1001;
  int dp[L][L];
  int wiggleMaxLength(vector<int>& nums) {
    memset(dp, 0, sizeof(dp));
    const int n = nums.size();

    for (int i = 0; i < n; ++i) {
      for (int prevIdx = i; prevIdx < n; ++prevIdx) {
        dp[i][prevIdx] = 1;
      }
    }

    for (int i = 1; i < n; ++i) {
      for (int j = 0; j < i; ++j) {
        for (int prevIdx = i; prevIdx < n; ++prevIdx) {
          int diff = nums[i] - nums[j];
          int prevDiff = nums[prevIdx] - nums[i];

          if (i == prevIdx) {
            if (sgn(diff) != SGN::NONE) {
              dp[i][prevIdx] = max(dp[i][prevIdx], 1 + dp[j][i]);
            }
          } else {
            if (sgn(diff) != SGN::NONE && sgn(prevDiff) != SGN::NONE &&
                sgn(diff) != sgn(prevDiff)) {
              dp[i][prevIdx] = max(dp[i][prevIdx], 1 + dp[j][i]);
            }
          }
        }
      }
    }

    int len = 0;

    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < n; ++j) {
        len = max(len, dp[i][j]);
      }
    }

    return len;
  }
};

namespace InitialSolution {

class Solution {
 public:
  static constexpr int L = 1001;
  int dp[L][L];
  bool vis[L][L];
  vector<int> n;
  int solve(const int i, const int prevIdx) {
    if (i < 0) return 0;
    if (vis[i][prevIdx]) return dp[i][prevIdx];
    vis[i][prevIdx] = true;

    int len = 1;
    // vector<int> l;
    for (int j = 0; j < i; ++j) {
      const int prevDiff = n[prevIdx] - n[i];
      const int diff = n[i] - n[j];

      if (i == prevIdx) {
        if (sgn(diff) != SGN::NONE) {
          len = max(1 + solve(j, i), len);
        }
      } else {
        if (sgn(diff) != SGN::NONE && sgn(prevDiff) != SGN::NONE &&
            sgn(diff) != sgn(prevDiff)) {
          len = max(1 + solve(j, i), len);
        }
      }
      // l.push_back(1 + solve(j, n[j] - n[i]));
    }
    // for(const int a : l) cout << a << "\n";
    return dp[i][prevIdx] = len;
  }
  int wiggleMaxLength(vector<int>& nums) {
    memset(vis, 0, sizeof(vis));
    n = move(nums);
    return solve(n.size() - 1, n.size() - 1);
  }
};

}  // namespace InitialSolution
