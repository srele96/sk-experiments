// https://leetcode.com/problems/counting-bits/?envType=problem-list-v2&envId=dynamic-programming

#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<int> countBits(int n) {
    if (n == 0) return {0};
    vector<int> dp(n + 1);
    dp[0] = 0;
    // Each new number starts at 2^n and requires us to get
    // each from 0 up to 2^n
    // Use counter, which starts at 2^0 and each time `c`
    // catches up to e, reset c and jump to next number 2^n.
    // It helps to imagine numbers like this:
    /*
    [0], [1], [2,3], [4,5,6,7], [8,9,10,11,12,13,14,15]
    [0000], [0001], [0010, 0011], [0100, 0101, 0110, 0111], [...]
    */
    int c = 0, e = 1;
    for (int i = 1; i < n + 1; ++i) {
      dp[i] = dp[c] + 1;
      ++c;
      if (c == e) {
        c = 0;
        e *= 2;
      }
    }
    return dp;
  }
};

/*

00 00
00 01
00 10
00 11
// observe 1 bit added to each previous
01 00
01 01
01 10
01 11
// new bit at 4th spot will be added to each previous
1 000 - 8 + 0
1 001 - 8 + 1
1 010 - 8 + 2
1 011 - 8 + 3
1 100 - 8 + 4
1 101 - 8 + 5
1 110 - 8 + 6
1 111 - 8 + 7

0000
0001
0010
0011
0100
0101
0110
0111
1000
1001
1010
1011
1100
1101
1110
1111

*/
