#include <bits/stdc++.h>
using namespace std;

// https://leetcode.com/problems/maximal-square/description/?envType=problem-list-v2&envId=dynamic-programming

namespace myIdeaButUsesIdeaFromBamboozledSolutionOfSides {

/*
Yay, this is awesome.
While, my idea works, even tho its different than the other one of overlapping
squares. And also, no more checking, if size zero or if valid or if valid then
sum up otherwise no, bla bla bla, all the ideas that can be noticed in the other
algorithm implementations of this one.
*/
static constexpr int L = 300;
static int box[L][L];
static int top[L][L];
static int l[L][L];

class Solution {
 public:
  template <size_t R, size_t C>
  void init(int (&arr)[R][C], int val = 0) {
    for (size_t i = 0; i < R; ++i)
      for (size_t j = 0; j < C; ++j) arr[i][j] = val;
  }
  int maximalSquare(vector<vector<char>>& m) {
    init(box);
    init(top);
    init(l);
    int r = 0;
    for (int i = 0; i < m.size(); ++i) {
      int v = m[i][0] - '0';
      box[i][0] = v;
      l[i][0] = v;
      top[i][0] = v;
      r = max(r, v);
    }
    for (int i = 0; i < m[0].size(); ++i) {
      int v = m[0][i] - '0';
      box[0][i] = v;
      top[0][i] = v;
      l[0][i] = v;
      r = max(r, v);
    }
    for (int i = 1; i < m.size(); ++i) {
      for (int j = 1; j < m[0].size(); ++j) {
        if (m[i][j] != '0') {
          int v = 1 + min({box[i - 1][j - 1], top[i - 1][j], l[i][j - 1]});
          box[i][j] = v;
          l[i][j] = v;
          top[i][j] = v;
          r = max(r, box[i][j]);
        }
      }
    }

    return r * r;
  }
};

}  // namespace myIdeaButUsesIdeaFromBamboozledSolutionOfSides

namespace bamboozledWhyDoesItWork {
/*
Honestly, this solution beats all reason. Somehow i keep seing a pattern where
DP solutions do not consider all cases **SOMEHOW** ...

I asked chatgpt to discuss, and he showed me this recurrence relation
And I was like... Bamboozled... Like, what the fuck?

dp[i][j] = 1 + min(dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1])

Observe... Why does this even work? It simply just DOES cover this case... Just
look!

1 1 1 1
1 1 1 1
1 1 1 1

00 01 02 03
10 11 12 13
20 21 22 23
30 31 32 33

00 -> 1
01 -> 1
02 -> 1
03 -> 1
10 -> 1

11 = 2 -
       - 00 = 1
       - 10 = 1
       - 01 = 1
12 = 2  -
       - 11 = 2
       - 01 = 1
       - 02 = 1

Where, number 2 represent the side 1s
Why does it work?
Not combinatorial?
Somehow this unintuitive numbering covers all the cases

*/
static constexpr int L = 300;
static int dp[L][L];
class Solution {
 public:
  int maximalSquare(vector<vector<char>>& m) {
    for (int i = 0; i < L; ++i) {
      for (int j = 0; j < L; ++j) {
        dp[i][j] = 0;
      }
    }

    int r = 0;

    for (int i = 0; i < m[0].size(); ++i) {
      dp[0][i] = m[0][i] - '0';
      r = max(r, dp[0][i]);
    }
    for (int i = 0; i < m.size(); ++i) {
      dp[i][0] = m[i][0] - '0';
      r = max(r, dp[i][0]);
    }

    for (int i = 1; i < m.size(); ++i) {
      for (int j = 1; j < m[0].size(); ++j) {
        if (m[i][j] == '1') {
          dp[i][j] = 1 + min({dp[i - 1][j - 1], dp[i - 1][j], dp[i][j - 1]});
          r = max(r, dp[i][j]);
        }
      }
    }

    return r * r;
  }
};

}  // namespace bamboozledWhyDoesItWork

/*

3 - 6
3 - 5
3 - 4
3 - 3
3 - 2
3 - 1
3 - 0

*/

/*

f(i, j, k):
  if (i == 0 || j == 0 || k == 0) return m[i][j] == '1' ? 1 : 0

  cell = m[i][j] == '1' ? 1 : 0
  inner = f(i - 1, j - 1, k - 1)
  top = f(i - 1, j, k - 1)
  left = f(i, j - 1, k - 1)

*/

/*
[
  ["0","0","0","0","0"],
  ["0","0","0","0","0"],
  ["0","0","0","0","1"],
  ["0","0","0","0","0"]]

*/

namespace topDownNMKK_TLE {

static const int LEN = 300;
static int dp[LEN][LEN][LEN];
// Still not good enough because of the loop inside making the algorithm
// O(n*m*k*k) Gotta try again If bottom up model of this didn't work Why did i
// even think a top down would lol
class Solution {
 public:
  vector<vector<char>> m;
  int f(int i, int j, int k) {
    // cout << i << ", " << j <<", " << k << "\n";
    if (i < 0 || j < 0 || k < 0) return 0;
    if (dp[i][j][k] != -1) return dp[i][j][k];

    int s = 0;
    for (int t = k; t >= 0; --t) {
      bool r = true;
      int v = 0;
      for (int a = i - t; a <= i; ++a) {
        for (int b = j - t; b <= j; ++b) {
          if (m[a][b] == '0') {
            r = false;
          } else {
            ++v;
          }
        }
      }
      // cout << i << ", " << j <<", " << t << ", " << v << "\n";
      if (r) s = max(s, v);
    }

    int r = max({
        s,
        f(i - 1, j - 1, k - 1),
        f(i - 1, j, k - 1),
        f(i, j - 1, k - 1),
    });
    if (i != j) {
      r = max(r, i > j ? f(i - 1, j, k) : f(i, j - 1, k));
    }
    return dp[i][j][k] = r;
  }

  int maximalSquare(vector<vector<char>>& matrix) {
    m = move(matrix);

    for (int i = 0; i < LEN; ++i) {
      for (int j = 0; j < LEN; ++j) {
        for (int k = 0; k < LEN; ++k) {
          dp[i][j][k] = -1;
        }
      }
    }

    int a = m.size() - 1, b = m[0].size() - 1, k = min(a, b);
    return f(a, b, k);
  }
};

}  // namespace topDownNMKK_TLE

/*
00 01 02 03 04
10 11 12 13 14
20 21 22 23 24
30 31 32 33 34
40 41 42 43 44
*/

namespace realizedMyStuffIsWrong {

/*
I think that this solution doesn't work.
It works as i expect it to.
I didn't see that a function that returns a MAX square with k sides to the left
of i,j indices is NOT what we want. The max square from 2,3,2 may be a square
with a side 1 which CAN NOT be combined with cell 3,4,3. Therefore, this
solution does NOT work. I have to rewrite it... i,j,k gives me either that
square or a zero if a square is not feasible.
*/
class Solution {
 public:
  vector<vector<char>> m;
  pair<int, bool> f(int i, int j, int k) {
    if (i == 0 || j == 0 || k == 0)
      return make_pair(m[i][j] - '0', m[i][j] == '1');

    pair<int, bool> r = make_pair(m[i][j] - '0', m[i][j] == '1');

    for (int t = 1; t < k; ++t) {
      pair<int, bool> top = make_pair(0, true);
      pair<int, bool> left = make_pair(0, true);
      for (int u = i - k; u < i; ++u) {
        if (m[u][j] == '0') {
          top.second = false;
          break;
        }
        ++top.first;
      }
      for (int u = j - k; u < j; ++u) {
        if (m[i][u] == '0') {
          left.second = false;
          break;
        }
        ++left.first;
      }
      pair<int, bool> inner = f(i - 1, j - 1, t);
      if (r.second && top.second && left.second && inner.second) {
        r.first = max(r.first, 1 + top.first + left.first + inner.first);
      }
    }

    if (i == j) {
      auto t = f(i - 1, j, k - 1);
      auto l = f(i, j - 1, k - 1);
      auto tl = f(i - 1, j - 1, k - 1);
      pair<int, bool> result;
      result.first = max({r.first, t.first, l.first, tl.first});
      result.second = result.first != 0;

      cout << "i == j, " << i << ", " << j << ", " << k
           << ", r.first = " << r.first << "\n";

      return result;
    }
    auto next = i > j ? f(i - 1, j, k) : f(i, j - 1, k);
    pair<int, bool> result;
    result.first = max(next.first, r.first);
    result.second = result.first != 0;
    cout << "i != j, " << i << ", " << j << ", " << k
         << ", r.first = " << r.first << "\n";
    return result;
  }

  int maximalSquare(vector<vector<char>>& matrix) {
    m = move(matrix);
    int a = m.size() - 1, b = m[0].size() - 1, k = min(a, b);
    auto result = f(a, b, k);
    cout << "result.second=" << result.second << "\n";
    return result.first;
  }
};

}  // namespace realizedMyStuffIsWrong

namespace tleButDpOptimized {

static int dp[300][300][300];

class Solution {
 public:
  int maximalSquare(vector<vector<char>>& matrix) {
    int n = matrix.size(), m = matrix[0].size();
    for (int i = 0; i < 300; ++i) {
      for (int j = 0; j < 300; ++j) {
        for (int k = 0; k < 300; ++k) {
          dp[i][j][k] = false;
        }
      }
    }

    for (int i = 0; i < n; ++i) {
      dp[i][0][0] = matrix[i][0] == '1';
    }
    for (int i = 0; i < m; ++i) {
      dp[0][i][0] = matrix[0][i] == '1';
    }

    for (int i = 1; i < n; ++i) {
      for (int j = 1; j < m; ++j) {
        // cout << i << ", " << j << ":\n";
        dp[i][j][0] = matrix[i][j] == '1';
        for (int k = min(i, j); k > 0; --k) {
          // cout << "k = " << k << ", ";
          int top = max(i - k, 0);
          int left = max(j - k, 0);
          // cout << "[" << top << ", " << left << "]";
          int box = true;
          // cout <<"a:\n";
          for (int a = top; a < i; ++a) {
            // cout << a << ", ";
            if (matrix[a][j] == '0') box = false;
          }
          // cout << "\n";
          for (int a = left; a < j; ++a) {
            if (matrix[i][a] == '0') box = false;
          }
          if (!dp[i - 1][j - 1][k - 1]) {
            box = false;
          }
          if (matrix[i][j] == '0') {
            box = false;
          }
          dp[i][j][k] = box;
          // int top = max(i - k, 0);
          // int left = max(j - k, 0);

          // cout << top << ", " << left << " | ";
        }
        // cout << "\n";
      }
    }
    int side = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        for (int k = 0; k < min(n, m); ++k) {
          // cout << i << ", " << j << ", " << k << "\n";
          if (dp[i][j][k]) {
            side = max(side, k + 1);
          }
        }
      }
    }
    return side * side;
  }
};

}  // namespace tleButDpOptimized

namespace tleBruteForce {

class Solution {
 public:
  int maximalSquare(vector<vector<char>>& matrix) {
    int n = matrix.size(), m = matrix[0].size();
    int s = 0;
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < m; ++j) {
        // cout << i << ", " << j << ":\n";
        for (int k = 0; k <= min(i, j); ++k) {
          int box = true;
          for (int a = max(i - k, 0); a <= i; ++a) {
            for (int b = max(j - k, 0); b <= j; ++b) {
              if (matrix[a][b] == '0') box = false;
            }
          }
          if (box) {
            s = max(s, k + 1);
          }
          // cout << max(i - k, 0) << ", " << max(j - k, 0) << " | ";
        }
        // cout << "\n";
      }
    }
    return s * s;
  }
};

}  // namespace tleBruteForce
