#include <bits/stdc++.h>
using namespace std;

namespace TwoDaysLater {

struct Key {
  size_t operator()(const pair<int, int>& p) const {
    return hash<int>()(p.first) ^ (hash<int>()(p.second) << 1);
  }
};

class Solution {
 public:
  unordered_map<pair<int, int>, int, Key> dp;
  vector<int> n;
  bool solve(const int i, const int target) {
    if (target < 0) return false;
    const pair<int, int> k = {i, target};
    if (dp.count(k)) return dp[k];
    if (target == 0) return dp[k] = true;
    if (i >= n.size()) return dp[k] = false;
    return dp[k] = solve(i + 1, target - n[i]) || solve(i + 1, target);
  }
  bool canPartition(vector<int>& nums) {
    n = move(nums);
    int total = 0;
    for (const int i : n) total += i;
    if (total % 2 != 0) return false;
    return solve(0, total / 2);
  }
};

}  // namespace TwoDaysLater

namespace TwoDaysBefore {

class Solution {
 public:
  int dp[201][10001];
  bool vis[201][10001];

  vector<int> n;
  bool solve(int i, int target) {
    if (i >= n.size() || target < 0) return false;
    if (target == 0) return dp[i][target] = true;
    if (vis[i][target]) return dp[i][target];
    vis[i][target] = true;

    int r = solve(i + 1, target - n[i]) || solve(i + 1, target);
    return dp[i][target] = r;
  }
  bool canPartition(vector<int>& nums) {
    memset(vis, 0, sizeof(vis));
    n = move(nums);
    int total = 0;
    for (const int i : n) total += i;
    if (total % 2 != 0) return false;
    return solve(0, total / 2);
  }
};

/*

Terrible.

Yeah.

Wrong.

The idea is as follows:
Attempt all possible partions.
We do not need to find a second partition.
We need to use all numbers.
The total/2 lookup guarantees that every partition will be a subset.

1
5
11
5

1,5
1,11
1,5
5,11
5,5
11,5

1,5,11
1,5,5
5,11,5

1,5,11,5

Tbh, i was blind.
I did not understand the problem. Again.
I already had all the subsets.
If i understood the problem, i would have been able to solve it myself.
How do I know that?
Because I understood what i need to do as soon as i got information:
- Use all numbers given
- A sum of two equal numbers is always even. ( Mathematical )
1+1=2
3+3=6
2+2=4


Proposition:
Start asking questions about the problem.
Should i use all numbers given?
Do the numbers of the two sets form the full initial given numbers? (Use all
numbers) Etc... So I can rectify the problem where I am solving a different
problem...

*/

/*
yeah, nah, the problem doesn't require sequential line-up

1 5 11 5

1           1
5           5
11          11
5           5

1 5         6
1 11        12
1 5         6
5 11        16
5 5         10
11 5        16

1 5 11      17
1 5 5       11
5 11 5      21

1 5 11 5    22

  1
  |
  ------------
  |    |     |
  5    11    5
  |
  ------
  |    |
  11   5
  |
  -
  |
  5


      5
      |
      ---------
      |   |   |
      11  5   11
      |
      -
      |
      5




1
1 5
  5
1 5 11
  5 11
    11
1 5 11 5
  5 11 5
    11 5
       5


0 + 4
[1 5 11 5]
1 + 3
[1] [5 11 5]

2 + 2
[1 5] [11 5]
[1] [5] [11 5]

3 + 1
[1 5 11] [5]
[1] [5 11] [5]
[1 5] [11] [5]
[1] [5] [11] [5]

*/

}  // namespace TwoDaysBefore
