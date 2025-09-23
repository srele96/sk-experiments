#include <bits/stdc++.h>
using namespace std;

// I SHOULD NOT HAVE DONE THIS PROBLEM -- GAME THEORY -- I DIDN'T PRACTICE GAME
// THEORY --
// -- I DID FIGURE OUT DP PART THO --
// Solved 75% by myself
// I think i might not be able to resolve by myeslf
// I don't understnad min(..., max(...)) inside
// Why does correct solution choose one child which is maximum
// But for the result we choose minimum
// Prolly because maximum value of child will give us the maximum sum
// And the minimum pivot + child is... no clue why
class Solution {
 public:
  int dp[201][201];
  int vis[201][201];
  int solve(int start, int end) {
    if (start >= end) return 0;
    if (vis[start][end]) return dp[start][end];
    vis[start][end] = true;
    int r = INT_MAX;
    for (int pivot = start; pivot <= end; ++pivot) {
      r = min(r, pivot + max(solve(start, pivot - 1), solve(pivot + 1, end)));
    }
    return dp[start][end] = r;
  }

  int getMoneyAmount(int n) {
    memset(vis, 0, sizeof(vis));
    return solve(1, n);
  }
};

namespace failure {

class Solution {
 public:
  int dp[201][201][201];
  int vis[201][201][201];
  int solve(int start, int end, int pivot) {
    if (start >= end) return 0;
    if (vis[start][end][pivot]) return dp[start][end][pivot];
    vis[start][end][pivot] = true;
    // cout << start << ", " << end << ", " << pivot << "\n";
    int lstart = start;
    int lend = pivot - 1;
    int lmin = INT_MAX;
    for (int i = lstart; i <= lend; ++i) {
      lmin = min(lmin, solve(lstart, lend, i));
    }
    if (lstart > lend) lmin = 0;

    int rstart = pivot + 1;
    int rend = end;
    int rmin = INT_MAX;
    for (int i = rstart; i <= rend; ++i) {
      rmin = min(rmin, solve(rstart, rend, i));
    }
    if (rstart > rend) rmin = 0;

    return dp[start][end][pivot] = pivot + max(lmin, rmin);
  }
  int getMoneyAmount(int n) {
    memset(vis, 0, sizeof(vis));
    int r = INT_MAX;
    for (int pivot = 1; pivot <= n; ++pivot) {
      r = min(r, solve(1, n, pivot));
      // cout << "pivot=" << pivot << ": " << solve(1, n, pivot) << ", " << r <<
      // "\n"; cout << "<<<<>>>>\n";
    }
    return r;
  }
};

/*

6
 7,10
  8
    9,10
      9
        10
    6,7
 1,5


7
  8,10
    9
      10,10
      8,8
  1,6
    3
      4,6
        5
          6,6
          4,4
      1,2
        1
          2,2

1,10

1
2
3
4
5
6

7
  1,6
    2
    3
      1,2
        1,1
        2,2
      4,6
    4
    5
  8,10
    9
      10,10
      8,8
8
9
10

*/

}  // namespace failure

/*

n=3

solve(1,3)
|- pivot=1: 1 + max(solve(1,0), solve(2, 3))
|  |- total=3
|  |- solve(1,0)
|  |  |- if(1 >= 0) return 0
|  |- solve(2,3)
|  |  |- pivot=2: 2 + max(solve(2,1), solve(3,3))
|  |  |  |- total=2
|  |  |  |- solve(2,1)
|  |  |  |  |- if (2 >= 1) return 0
|  |  |  |- solve(3,3)
|  |  |  |  |- if (3 >= 3) return 0
|  |  |- pivot=3: 3 + max(solve(1,2), solve(4,3))
|  |  |  |- solve(1,2)
|  |  |  |  |- pivot=1: 1 + max(solve(1,0), solve(2, 2))
|  |  |  |  |  |- solve(1,0)
|  |  |  |  |  |  |- if (1 >= 0) return 0
|  |  |  |  |  |- solve(2,2)
|  |  |  |  |  |  |- if (2 >= 2) return 0
|  |  |  |  |- pivot=2: 2 + max(solve(1,1), solve(3,2))
|  |  |  |  |  |- solve(1,1)
|  |  |  |  |  |  |- if (1 >= 1) return 0
|  |  |  |  |  |- solve(3,2)
|  |  |  |  |  |  |- if (3 >= 2) return 0
|  |  |  |- solve(4,3)
|  |  |  |  |- if (4 >= 3) return 0
|
|- pivot=2: 2 + max(solve(1,1), solve(3,3)) => 2
|  |- solve(1,1)
|  |  |- if (1 >= 1) return 0
|  |
|  |- solve(3,3)
|  |  |- if (3 >= 3) return 0
|
|- pivot=3: 3 + max(solve(1,2), solve(4,3)) => 4
   |- solve(1,2)
   |  |- pivot=1: 1 + max(solve(1,0), solve(2,2))
   |     |- solve(1,0)
   |     |  |- if (1 >= 0) return 0
   |     |
   |     |- solve(2,2)
   |        |- if (2 >= 2) return 0
   |
   |  |- pivot=2: 2 + max(solve(1,1), solve(3,2))
   |     |- solve(1,1)
   |     |  |- if (1 >= 1) return 0
   |     |
   |     |- solve(3,2)
   |        |- if (3 >= 2) return 0
   |
   |- solve(4,3)
      |- if (4 >= 3) return 0

solve(1,10)
|- pivot=1
|- pivot=2
|- pivot=3
|- pivot=4
|- pivot=5
|- pivot=6
|- pivot=7: cost = 7 + max(solve(1,6), solve(8, 10))
|  |- solve(1, 6): try pivots 1,2,3,4,5,6
|  |  |- pivot=1
|  |  |- pivot=2
|  |  |- pivot=3
|  |  |- pivot=4
|  |  |- pivot=5
|  |  |- pivot=6
|  |- solve(8, 10): try pivots 8,9,10
|  |  |- pivot=8
|  |  |- pivot=9: cost = 9 + max(solve(8, 8), solve(10, 10))
|  |  |  |- solve(8, 8)
|  |  |  |  |- if (8 >= 8) return 0
|  |  |  |- solve(10, 10)
|  |  |  |  |- if (10 >= 10) return 0
|  |  |- pivot=10
|- pivot=8
|- pivot=9
|- pivot=10

    1,0

    2,10

  2

  3

  4

  5

  6

  7

    1,6

    8,10

      8

        8,7

        9,10

          9

            9,8

            10,10

              10

                10,9

                11,10

          10

      9

        8,8

        10,10

      10

  8

  9

  10

*/

/*
Unverified by gpt (he fixed my tree)

solve(1,3) - find MIN of all pivots
├─ pivot=1: 1 + max(solve(1,0), solve(2,3))
│  ├─ solve(1,0) = 0 (base case: 1 >= 0)
│  └─ solve(2,3) - find MIN of pivots 2,3
│     ├─ pivot=2: 2 + max(solve(2,1), solve(3,3))
│     │  ├─ solve(2,1) = 0 (base case: 2 >= 1)
│     │  ├─ solve(3,3) = 0 (base case: 3 >= 3)
│     │  └─ cost = 2 + max(0,0) = 2
│     ├─ pivot=3: 3 + max(solve(2,2), solve(4,3))
│     │  ├─ solve(2,2) = 0 (base case: 2 >= 2)
│     │  ├─ solve(4,3) = 0 (base case: 4 >= 3)
│     │  └─ cost = 3 + max(0,0) = 3
│     └─ solve(2,3) = MIN(2,3) = 2
│  └─ pivot=1 total = 1 + max(0,2) = 1 + 2 = 3
│
├─ pivot=2: 2 + max(solve(1,1), solve(3,3))
│  ├─ solve(1,1) = 0 (base case: 1 >= 1)
│  ├─ solve(3,3) = 0 (base case: 3 >= 3)
│  └─ pivot=2 total = 2 + max(0,0) = 2
│
└─ pivot=3: 3 + max(solve(1,2), solve(4,3))
   ├─ solve(1,2) - find MIN of pivots 1,2
   │  ├─ pivot=1: 1 + max(solve(1,0), solve(2,2))
   │  │  ├─ solve(1,0) = 0 (base case: 1 >= 0)
   │  │  ├─ solve(2,2) = 0 (base case: 2 >= 2)
   │  │  └─ cost = 1 + max(0,0) = 1
   │  ├─ pivot=2: 2 + max(solve(1,1), solve(3,2))
   │  │  ├─ solve(1,1) = 0 (base case: 1 >= 1)
   │  │  ├─ solve(3,2) = 0 (base case: 3 >= 2)
   │  │  └─ cost = 2 + max(0,0) = 2
   │  └─ solve(1,2) = MIN(1,2) = 1
   ├─ solve(4,3) = 0 (base case: 4 >= 3)
   └─ pivot=3 total = 3 + max(1,0) = 3 + 1 = 4

Final: solve(1,3) = MIN(3,2,4) = 2

*/
