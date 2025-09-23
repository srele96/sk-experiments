#include <bits/stdc++.h>
using namespace std;

struct Key {
  size_t operator()(const pair<int, int>& p) const {
    return hash<int>()(p.first) ^ hash<int>()(p.second);
  }
};
class Solution {
 public:
  int n = 0;
  // unordered_map<pair<int,int>, bool, hash<pair<int,int>>> dp;
  unordered_map<size_t, bool> dp;
  bool solve(const int avail, const int target) {
    // I suppose this is also very interesting.
    // The maximum value of int fits in size_t so we can shift it by 32 bits
    // left And we can add the target bits to the key Then we can use that value
    // as a key preserving combination of both information Bitmasking is
    // actually so cool, when you think about it O_O No wonder facebook folks
    // used bitmasking for child tracking implementation
    size_t k = (static_cast<size_t>(avail) << 32) | target;
    // const pair<int,int> k = make_pair(avail, target);
    if (dp.count(k)) return dp[k];
    if (target <= 0) return dp[k] = true;
    for (int i = 1; i <= n; ++i) {
      if (avail & (1 << i)) {
        if (i >= target || !solve(avail & ~(1 << i), target - i)) {
          return dp[k] = true;
        }
      }
    }
    return dp[k] = false;
  }
  bool canIWin(int ints, int desiredTotal) {
    n = ints;
    int sum = (n * (n + 1)) / 2;
    if (sum < desiredTotal) return false;
    if (desiredTotal == 0) return true;

    int avail = 0;
    for (int i = 1; i <= n; ++i) {
      avail |= (1 << i);
    }
    return solve(avail, desiredTotal);
  }
};

/*

the path which makes the adversary unable to reach the number

1...15
100

1
2
3
4
5
...


1...2

2
  1
1
  2

1...3
target=6
for targets 1,2,3 i can always win, no matter the choice
for targets 4 (i can't always win):
  me: 1
  adv: 3 (wins)
  --
  me: 2
  adv: 3 (wins)
  --
  me: 3
  adv: 1 (wins)
  --
  me: 3
  adv: 2 (wins)
for targets: 5


target - myChoice

1
  2
    3
  3
    2
2
  1
    3
  3
    1
3
  1
    2
  2
    1

target=10
  1
    target=9
    2
      target=7
      3
        target=6
        4
        target=5
        5
      4
      5
    3
    4
    5
  2
  3
  4
  5


optimal choice...
is there an optimal choice...
at each step...

*/
