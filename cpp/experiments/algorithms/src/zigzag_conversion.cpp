#include <bits/stdc++.h>
using namespace std;

// https://leetcode.com/problems/zigzag-conversion/

/*

Observe a table of arithmetic progression. Where the formula for the nth element
is:

a_n = a_0 + d * (n - 1)

Notice that the distances in each row between two elements are equal. However
there are 2 distances per each zig-zag row. Taking a notice at these properties
allows us to use arithmetic progression to manipulate the state of numbers and
access the corresponding string index.


______________________________________________________________
|  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  10  |
______________________________________________________________


______________________________
|  1 |  3  |  5  |  7  |  9  |
______________________________
|  2 |  4  |  6  |  8  |  10 |
______________________________


________________________________
|  1  |     |  5  |     |  9   |
________________________________
|  2  |  4  |  6  |  8  |  10  |
________________________________
|  3  |     |  7  |     |      |
________________________________


_________________________
|  1  |     |     |  7  |
_________________________
|  2  |     |  6  |  8  |
_________________________
|  3  |  5  |     |  9  |
_________________________
|  4  |     |     |  10 |
_________________________


_______________________________
|  1  |     |     |     |  9  |
_______________________________
|  2  |     |     |  8  |  10 |
_______________________________
|  3  |     |  7  |     |     |
_______________________________
|  4  |  6  |     |     |     |
_______________________________
|  5  |     |     |     |     |
_______________________________


_______________________________
|  1  |     |     |     |     |
_______________________________
|  2  |     |     |     |  10 |
_______________________________
|  3  |     |     |  9  |     |
_______________________________
|  4  |     |  8  |     |     |
_______________________________
|  5  |  7  |     |     |     |
_______________________________
|  6  |     |     |     |     |
_______________________________

*/

/**

-------------
1 2 3 4 5 6 7
-------------
1 3 5 7
2 4 6
-------------
1 4 7
2 5
3 6
-------------
1 5
2 6
3 7
4
-------------
1 6
2 7
3
4
5
-------------
1 7
2
3
4
5
6
-------------
1
2
3
4
5
6
7
-------------

**/

namespace a {
class Solution {
 public:
  string convert(string s, int numRows) {
    bool zig = true;
    array<string, 1000> strs;
    function<void(int, int, int, int)> zigzag = [&](int r, int i, int j,
                                                    int c) {
      if (c < s.length()) {
        strs[i] += s[c];

        if (r != 0) {
          if (i == 0) zig = true;
          if (i == r) zig = false;

          if (zig) {
            zigzag(r, i + 1, j, c + 1);
          } else {
            zigzag(r, i - 1, j + 1, c + 1);
          }
        } else {
          zigzag(r, i, j + 1, c + 1);
        }
      }
    };

    zigzag(numRows - 1, 0, 0, 0);
    string res;
    for (int i = 0; i < numRows; ++i) res += strs[i];

    return res;
  }
};
}  // namespace a

namespace b {
class Solution {
 public:
  string convert(string s, int numRows) {
    int i = 0, c = 0;
    bool zig = true;
    array<string, 1000> arr;
    while (c < s.length()) {
      arr[i] += s[c];
      // If we can go zig-zag
      if (numRows != 0) {
        // I also know intuitively that zig = i == 0; won't work and I
        // believe that. But I do not intuitively believe that the recursive
        // solution I pulled from long term memory had worked... Because I
        // have mostly negative experiences writing solution to an
        // algorithmic problem if I didn't check the state on the paper.
        if (i == 0) zig = true;
        if (i == numRows - 1) zig = false;
        if (zig && i < numRows - 1) ++i;
        if (!zig && i > 0) --i;
      }
      ++c;
    }
    string res;
    for (int i = 0; i < numRows; ++i) res += arr[i];
    return res;
  }
};
}  // namespace b

namespace c {
// After a first glance at the image from the link below, I saw an arrow, and
// realized we can have a directed graph or some kind of graph here. Because
// as we iterate I believe we can build connections and stuff like that, maybe
// not initially, but maybe we can build a graph as we go zig-zag and not
// initially from the state as the initial state is a linear string. Graph is
// a data structure that displays connections... relationships. We could
// observe an array as a graph where each element points to the left and right
// one, but it's not any more complex than that. Maybe... Always maybe...
// https://leetcode.com/problems/zigzag-conversion/discuss/5338874/A-revolutionary-solution-that-you-haven't-seen-before
class Solution {
  string convert(string s, int numRows) {}
};
}  // namespace c
