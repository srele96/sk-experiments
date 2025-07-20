#include <bits/stdc++.h>
using namespace std;

// https://leetcode.com/problems/maximum-product-subarray/?envType=problem-list-v2&envId=dynamic-programming

// O(n log (n)) or faster ... damn

class Solution {
 public:
  /*
  1
  1,2
    2
  1,2,3
    2,3
      3
  1,2,3,4
    2,3,4
      3,4
        4

  2

  2, -5
  -5

  2, -5, -2
  -5, -2
  -2

  2, -5, -2, -4
  -5, -2, -4
  -2, -4
  -4

  0,0

  0,1
  1,0

  0,2
  1,2
  2,2

  0,3 = (0,2) * (0,3)
  1,3 = (1,3) * (1,2)
  2,3 = (2,3) * (2,2)
  3,3 = (3,3)

  0,0 = n[0]

  0,1 = n[1] * (0,0)
  1,0 = n[1]

  0,2 = n[2] * (0, 1)
  1,1 = n[2] * (1, 0)
  2,0 = n[2]

  0,4 = n[3] * (0,2)
  1,3 = n[3] * (1,1)
  2,2 = n[3] * (2,0)
  3,1 = n[3] * (3,)

  1,1 = n[0] * (1, 0)

  1,2 = n[1] * (1, 1)
  2,1 =

  1,3
  2,2
  3,1

  1,1 = n[0] * (1, 0)

  2,2 = n[1] * (2, 1)
  1,2 = n[1] * (1, 1)

  1,3 = n[2] * (1, 2)
  2,3 = n[2] * (2, 2)
  3,3 = n[2] * (3, 2)

  1,4
  2,4
  3,4
  4,4

  1
  1,2
    2
  1,2,3
    2,3
      3
  1,2,3,4
    2,3,4
      3,4
        4
  1,2,3,4,5
    2,3,4,5
      3,4,5
        4,5
          5

  */
  vector<int> n;
  int f() {
    int m = n.size();
    // vector<vector<int>> dp(m + 1, vector<int>(m + 1));
    unordered_map<int, unordered_map<int, int>> dp;
    for (int i = 1; i <= m; ++i) dp[i][i - 1] = 1;

    int r = INT_MIN;
    for (int i = 1; i <= m; ++i) {
      for (int j = 1; j <= i; ++j) {
        // cout << j << ", " << i << "\n";
        dp[j][i] = n[i - 1] * dp[j][i - 1];
        r = max(r, dp[j][i]);
      }
      // cout << "\n";
    }
    return r;
  }
  int maxProduct(vector<int>& nums) {
    n = move(nums);
    return f();
  }
};

/*
2
  2,3
     2,3,-2
            2,3,-2,4
            2,3,(-2)*4
     2,3*(-2)
            2,3*(-2),4
            2,3*(-2)*4
  2*3
*/

/*
1
1,2
1,2,3
  2,3
    3
1,2,3,4
  2,3,4
    3,4
      4
*/
