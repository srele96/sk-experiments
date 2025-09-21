#include <bits/stdc++.h>
using namespace std;

/*
Interestingly... Some DP problems are easier bottom-up (like this one)
Other DP problems are easier top-down...
Sometimes recursion isn't the easiest to 'see' the states...
*/
class Solution {
 public:
  vector<int> nums;
  static constexpr int L = 2500;
  int dp[L];

  // int solve(int i) {
  //   if (dp[i] > 1) return dp[i];
  //   int r = 1;
  //   for(int j = 0; j < i; ++j) {
  //     if (nums[i] > nums[j]) {
  //       r = max(r, solve(j) + 1);
  //     }
  //   }
  //   return dp[i] = r;
  // }

  int lengthOfLIS(vector<int>& _nums) {
    nums = move(_nums);
    for (int i = 0; i < L; ++i) {
      dp[i] = 1;
    }
    for (int i = 1; i < nums.size(); ++i) {
      for (int j = 0; j < i; ++j) {
        if (nums[i] > nums[j]) {
          dp[i] = max(dp[i], dp[j] + 1);
        }
      }
    }
    int r = 0;
    for (int i = 0; i < nums.size(); ++i) {
      r = max(r, dp[i]);
    }

    // ----
    // for(int i = 0; i < nums.size(); ++i) {
    //   r = max(r, solve(i));
    // }
    return r;
  }
};
