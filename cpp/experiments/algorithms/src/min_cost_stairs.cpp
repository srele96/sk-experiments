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



f(n):
  if n == 0 return
  f(n - 1)



f(n):
  if n == 0 return
  f(n - 1)
  f(n - 1)



                    n
         n-1                   n-1
    n-1       n-1        n-1        n-1
n-1   n-1  n-1  n-1   n-1   n-1  n-1   n-1


count calls on each level


f(n)    1
f(n-1)  2
f(n-2)  4
f(n-3)  8



f(n):
  if n == 0 return

  f(n - 1)
  f(n - 1)
  f(n - 1)


                                                n

      n - 1                                   n - 1                             n - 1

n - 1      n - 1      n - 1        n - 1      n - 1      n - 1       n - 1      n - 1      n - 1

count calls on each level

f(n)       1
f(n-1)     3
f(n-2)     9
f(n-3)     27
f(n-4)     81
f(n-5)     242

current level has 3 * calls of previous level
so for n = 1, we have 1
for n = 2, we have 3 * 1 calls, equal 3
for n = 3, we have 3 * (3 * 1) calls, equal 9
for n = 4, we have 3 * (3 * (3 * 1)), equal 27
for n = 5, we have 3 * (3 * (3 * (3 * 1))), equal 81

from that we can observe that for each level we have the number of calls for
one function which is 3, is repeated n-1 times,
for level 2, we have number 3 appear 1 time
for level 3, we have number 3 appear 2 times
for level 4, we have number 3 appear 3 times
for level 5, we have number 3 appear 4 times

therefore for level n, we have number 3 appear n-1 times



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
