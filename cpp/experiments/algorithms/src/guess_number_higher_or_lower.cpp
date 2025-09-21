#include <bits/stdc++.h>
using namespace std;

/**
 * Forward declaration of guess API.
 * @param  num   your guess
 * @return 	     -1 if num is higher than the picked number
 *			      1 if num is lower than the picked number
 *               otherwise return 0
 * int guess(int num);
 */

/*



*/

class Solution {
 public:
  int guessNumber(int n) {
    int l = 1, r = n, m = l + (r - l) / 2, g = guess(m);

    while (g != 0) {
      if (g == 1) {
        l = m + 1;
      } else {
        r = m - 1;
      }
      m = l + (r - l) / 2;
      g = guess(m);
    }

    return m;
  }
};
