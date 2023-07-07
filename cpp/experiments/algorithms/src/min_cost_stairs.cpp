#include <bits/stdc++.h>
using namespace std;

/*


* start from 0 or 1
* pay step then go to step + 1 or step + 2
* recursion, same choice repeats for nth step
* dp
* choice of the most optimal step


[0, 0]
[999, 999]
[0, 1]
[1, 0]
[999, 0]
[0, 999]
[5, 5]
[3, 5, 1] -> n[0] + n[2]
[5, 5, 5, 5, 5, 5] -> n[1] + n[1 + 2] + n[3 + 2]


go from the end because we can start from the end and we need to know what is
the price of the next step each step has a choice n[i + 1] or n[i + 2] and...
from n[i] we chose go n[i] + min(n[i+1], n[i+2])
i < n


from the following, we can see the recursive function generates the following
trees without dynamic programming

E -> indicates end beyond last index

[a, b]
generate tree for each index
  0
 / \
1   E

  1
 /
E

[a,b,c]
generate tree for each index

    0
   / \
  1   2
 / \   \
2   E   E

  1
 / \
2   E

  2

[a, b, c, d]
generate tree for each index

          0
      /       \
     1         2
   /  \       / \
  2    3     3   E
 / \   /    /
3   E E    E

     1
   /   \
  2     3
 / \   /
3   E E

  2
 / \
3   E

  3
 /
E

mcs(c):
  l = c.len, dp[l)
  mc(i):
    if (dp[i]) return dp[i]
    if (i < l):
      dp[i] = min(c[i] + mc(i + 1), c[i] + mc(i + 2))
      return d[i]
    else return 0
  return min(mc(0), mc(1))

*/

// class Solution {
// public:
//     int minCostClimbingStairs(vector<int>& cost) {
//         int l = cost.size();
//         vector<int> dp(l);
//         dp[l - 1] = cost[l - 1];
//         dp[l - 2] = cost[l - 2];
//         for(int i = l - 3; i >= 0; --i)
//             dp[i] = min(cost[i] + dp[i + 1], cost[i] + dp[i + 2]);
//         return min(dp[0], dp[1]);
//     }
// };

// class Solution {
// public:
//     int minCostClimbingStairs(vector<int>& cost) {
//         vector<int> dp(cost.size(), -1);
//         struct R{
//             int operator()(int i, vector<int>&dp, const vector<int>&cost) {
//                 if (i < cost.size()) {
//                     if (dp[i] >= 0) return dp[i];
//                     dp[i] = min(cost[i] + (*this)(i + 1, dp, cost), cost[i] +
//                     (*this)(i + 2, dp, cost)); return dp[i];
//                 } else {
//                     return 0;
//                 }
//             }
//         };
//         return min(R{}(0,dp,cost), R{}(1,dp,cost));
//     }
// };

class Solution {
 public:
  int minCostClimbingStairs(vector<int>& cost) {
    vector<int> dp(cost.size(), -1);
    function<int(int)> c = [&](int i) {
      if (i < cost.size()) {
        if (dp[i] >= 0) return dp[i];
        dp[i] = min(cost[i] + c(i + 1), cost[i] + c(i + 2));
        return dp[i];
      } else {
        return 0;
      }
    };
    return min(c(0), c(1));
  }
};
