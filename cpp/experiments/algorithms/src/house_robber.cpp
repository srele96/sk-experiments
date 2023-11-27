#include <bits/stdc++.h>
using namespace std;

// https://leetcode.com/problems/house-robber/

/*

1, 400 -> n[1]
1, 400, 1 -> n[1]
1, 1, 400 -> n[0] + n[2]
1, 1, 1, 400 -> n[0] + n[3], n[1] + n[3]
3, 1, 400 -> n[0] + n[2]
3, 1, 1, 400 -> n[0] + n[3]
1, 2, 3, 400, 400 ->


n[0] + n[2] + n[4]
n[1] + n[3] + n[5]
       n[2] + n[4]
       n[3] + n[5]
              n[4]
n[0] + n[3] + n[5]
n[1] + n[4]


// not gonna work...
dp[n.len]
s(i):
while(i < len):
  if (n[i + 2] < n[i + 3])
    dp[i] = n[i] + n[i + 2]
    i += 4
  else:
    dp[i] = n[i] + n[i + 3]
    i += 5
return max(s[0], s[1])




n[i] + n[i+2] -> next i is i + 4
n[i] + n[i+3] -> next i is i + 5

0 1 2 3 4
0   2
0     3


s(i):
  if i < n.len:
    if dp[i]: return dp[i]
    dp[i] = n[i] + min(s(i + 2), s(i + 3))
    return dp[i]
  else:
    return 0
return min(s(0), s(1))

*/

class Solution {
 public:
  int rob(vector<int>& nums) {
    vector<int> dp(nums.size(), -1);
    function<int(int)> s = [&](int i) {
      if (i < nums.size()) {
        if (dp[i] >= 0) return dp[i];
        dp[i] = nums[i] + max(s(i + 2), s(i + 3));
        return dp[i];
      } else {
        return 0;
      }
    };
    return max(s(0), s(1));
  }
};
