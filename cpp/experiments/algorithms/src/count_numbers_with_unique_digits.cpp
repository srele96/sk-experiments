#include <bits/stdc++.h>
using namespace std;

namespace NewSolutions {

template <size_t L = 8>
struct V {
  int dp[L];
  constexpr V() : dp{} {
    dp[0] = 10;
    dp[1] = 9 * 9;
    for (int i = 2; i < L; ++i) {
      dp[i] = (10 - i) * dp[i - 1];
    }
  }
};

class Solution {
 public:
  constexpr int countNumbersWithUniqueDigits(int n) {
    constexpr V v;

    if (n == 0) return 1;
    int r = 0;
    for (int i = 0; i < n; ++i) {
      r += v.dp[i];
    }
    return r;
  }
};

namespace UseLoop {

class Solution {
 public:
  int countNumbersWithUniqueDigits(int n) {
    int dp[9];
    dp[0] = 1;
    dp[1] = 10;
    dp[2] = 9 * 9;
    for (int i = 3; i <= 8; ++i) {
      dp[i] = (11 - i) * dp[i - 1];
    }
    if (n == 0) return dp[0];
    int r = 0;
    for (int i = 1; i <= n; ++i) {
      r += dp[i];
    }
    return r;
  }
};

}  // namespace UseLoop

}  // namespace NewSolutions

/*

1
  0
  2
  3
  4
  5
  6
  7
  8
  9
2
3
4
5
6
7
8
9

*/

template <size_t L = 9>
struct DP {
  int dp[L];
  constexpr DP() : dp{} {
    dp[0] = 1;
    dp[1] = 10;
    dp[2] = 9 * 9;
    dp[3] = 8 * dp[2];
    dp[4] = 7 * dp[3];
    dp[5] = 6 * dp[4];
    dp[6] = 5 * dp[5];
    dp[7] = 4 * dp[6];
    dp[8] = 3 * dp[7];
  }
};

static constexpr DP dp;

class Solution {
 public:
  int countNumbersWithUniqueDigits(int n) {
    // Alternative solution...
    if (n == 0) return dp.dp[n];
    int r = 0;
    for (int i = 1; i <= n; ++i) {
      r += dp.dp[i];
    }
    return r;
  }
};

namespace initialSolution {

class Solution {
 public:
  // int solve(int level, int target, const set<int>& used) {
  //   if (used.size() == target) return 1;

  //   int digits = 0;
  //   cout << "level=" << level << "\n";
  //   for(int i = level > 0 ? 0 : 1; i <= 9; ++i) {
  //     if (!used.count(i)) {
  //       set<int> s = used;
  //       s.insert(i);
  //       cout << "i=" << i << "\n";
  //       digits += 1 + solve(level + 1, target, s);
  //       cout << "----\n";
  //     }
  //   }
  //   return digits;
  //   return 0;
  // }
  int solve(const int n) {
    if (n == 0) return 1;
    if (n == 1) return 10;
    int r = 9;
    for (int i = 9; i >= 11 - n; --i) {
      r *= i;
    }
    r += solve(n - 1);
    return r;
  }
  int countNumbersWithUniqueDigits(int n) { return solve(n); }
};

}  // namespace initialSolution

/*

The whole idea comes from dynamic programming approach (per my understanding...)
Unique numbers have DP structure and can be build as follows

0
1
2
3
4
5
6
7
8
9

These are 1 digit numbers

Two digit numbers start with number 1, which gives us count of 9
To one digit, we can append other 9 digits 0...9 with exception of given used
digit Which gives us 9*9 amount of 2 digit numbers and previously computed 10 1
digit numbers

1
  0
  2
  3
  4
  5
  6
  7
  8
  9
2
  0
  1
  3
  4
  5
  6
  7
  8
  9
3
4
5
6
7
8
9

Then we proceed to generate 3 digit numbers, which follows the same pattern
We notice that at 3rd digit, we are using only 8 digits, for example

To make digit `10` a 3 digit number we have `2,3,4,5,6,7,8,9` which is 8
Since we have 2 digit numbers, by math, each of them has 8 valid ways to become
3 digit number

The amount of 3 digit numbers: (9*9 + 10) * 8

And at 3 digit numbers, we have in total:

1 digit numbers: 10
2 digit numbers: (9 * 9) = 91
3 digit numbers: (9 * 9 * 8) = 648

1
  0
    2
    3
    4
    5
    6
    7
    8
    9
  2
  3
  4
  5
  ...
2
3
...

*/

/*

We recognize 2 recursions here:
Compute digits at given level.
Sum digits up to given level.

0: 1
1: 10
2: 9*9
3: 9*9*8
4: 9*9*8*7
5: 9*9*8*7*6
6: 9*9*8*7*6*5
7: 9*9*8*7*6*5*4
8: 9*9*8*7*6*5*4*3

11-1 = 10
11-2 = 9
11-3 = 8
11-8 = 3

digits(n)
  if n == 0 return 1
  if n == 1 return 10
  return 9 * (11 - n) * digits(n - 1)

*/

/*

0: 1, 2, 3, 4, 5, 6, 7, 8, 9, 12, 13, 14, 15,

100 000 000
800 000 000
*/

/*

9
1
2
3
4
5
6
7
8
10
12
13
14
15
16
17
18
19
20
21
23
24
25
26
27
28
29
30
31
32
33
34
35
36
101
102
103
104
105
106
107
108
109
120
121
123
124
125
126
127
128
129
130
132
134


11
22
23
33
44
55
66
77
88
99

100
101

110
111
112
113
114
115
116
117
118
119

121
122

131
133

141
144

151
155

161
166

171
177

181
188

191
199

200
201


level = amount of digits
set = disallowed digits

n=0, 1
n=1, 10
n=2, 9 * 9 + 10
n=3, 9 * 9 * 8 + 9*9 + 10
n=4, 9 * 9 * 8 * 7   +   9 * 9 * 8   +   9 * 9  + 10
n=5  9 * 9 * 8 * 7 * 6
n=6  9 * 9 * 8 * 7 * 6 * 5
n=7  9 * 9 * 8 * 7 * 6 * 5 * 4
n=8  9 * 9 * 8 * 7 * 6 * 5 * 4 * 3


solve(n)
  if n == 0 return 1
  if n == 1 return 10
  int r = 9;
  for(int i = 9; i >= 11 - n; --i) {
    r *= i;
  }
  r += solve(n - 1)
  return r

god damn it until i found the mathematical pattern for this sh!t



0
1
  0
    2
    3
    4
    5
    6
    7
    8
    9
  2
    1
    3
    4
    5
    6
    7
    8
    9
  3
    2
    4
    5
    6
    7
    8
    9
  4
  5
  6
  7
  8
  9
2
3
4
5
6
7
8
9

1
  0
    2
      3
        4
          5
            6
              7
                8
                  9
                9
                  8
              8
                7
                  9
                9
                  7
              9
            7
            8
            9
          6
          7
          8
          9
        5
        6
        7
        8
        9
      4
      5
      6
      7
      8
      9
    3
    4
    5
    6
    7
    8
    9
  2
    0
  3
  4
  5
  6
  7
  8
  9
2
  0
  1
  3
  4
  5
  6
  7
  8
  9
3
  0
  1
  2
  3
  4
  5
  6
  7
  8
  9
4
5
6
7
8
9

1
  0
    2
      3
        4
        5
        6
        7
        8
        9
      4
        3
        5
        6
        7
        8
        9
      5
      6
      7
      8
      9
    3
    4
    5
    6
    7
    8
    9
    10
  2
  3
  4
  5
  6
  7
  8
  9


1
  0
    0
    1
  1
    0
    1
  2
    1
    2
  3
    1
    3
  4
    1
    4
  5
    1
    5
  6
    1
    6
  7
    1
    7
  8
    1
    8
  9
    1
    9
2
  0
    2
  1
    2
  2
    2
  3
    2
  4
    2
  5
    2
  6
    2
  7
    2
  8
    2
  9
    2
3
  3
4
  4
5
  5
6
  6
7
  7
8
  8
9
  9
*/
