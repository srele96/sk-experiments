#include <bits/stdc++.h>
using namespace std;

// 1,1    1
// 1,2    2
// 1,3    3
// 2,1    4
// 2,2    5
// 2,3    6
// 3,1    7
// 3,2    8
// 3,3    9

// 0,0 > 0
// 0,1 > 1
// 0,2   2
// 1,0 > 3
// 1,1 > 4
// 1,2   5
// 2,0   6
// 2,1   7
// 2,2   8

class Solution {
 public:
  vector<int> r;
  vector<vector<int>> m;

  void _solve(const int i, const int j, const bool up = true) {
    // cout << i << ", " << j << ", " << up << "\n";
    r.push_back(m[i][j]);
    if (i == m.size() - 1 && j == m[0].size() - 1) return;
    if (up) {
      const int row = i - 1;
      const int col = j + 1;
      const bool badRow = row < 0;
      const bool badCol = col >= m[0].size();
      if (badRow && badCol)
        return _solve(i + 1, j, false);
      else if (badRow)
        return _solve(i, col, false);
      else if (badCol)
        return _solve(i + 1, j, false);
      else
        return _solve(row, col, true);
    }
    const int row = i + 1;
    const int col = j - 1;
    const bool badRow = row >= m.size();
    const bool badCol = col < 0;
    if (badRow && badCol)
      return _solve(i, j + 1, true);
    else if (badRow)
      return _solve(i, j + 1, true);
    else if (badCol)
      return _solve(row, j, true);
    else
      return _solve(row, col, false);
  }

  void solve(const int i, const int j, const bool down = false) {
    // cout << i << ", " << j << ", " << down << "\n";
    r.push_back(m[i][j]);
    if (i == m.size() - 1 && j == m[0].size() - 1) return;
    if (down) {
      const int row = i + 1;
      const int col = j - 1;
      const bool rbad = row == m.size();
      const bool cbad = col < 0;

      if (rbad && cbad) return solve(i, j + 1, false);
      if (rbad) return solve(i, j + 1, false);
      if (cbad) return solve(row, j, false);
      return solve(row, col, down);
    }
    const int row = i - 1;
    const int col = j + 1;
    const bool rbad = row < 0;
    const bool cbad = col == m[0].size();
    if (rbad && cbad) return solve(i + 1, j, true);
    if (rbad) return solve(i, col, true);
    if (cbad) return solve(i + 1, j, true);
    return solve(row, col, down);
  }

  // This approach is based on the recursive solution, without call stack
  // overhead.
  vector<int> f() {
    int i = 0, j = 0, row = 0, col = 0;
    bool up = true, badRow = false, badCol = false;
    int idx = 0;
    vector<int> result(m.size() * m[0].size());
    while (true) {
      result[idx] = m[i][j];
      ++idx;
      if (i == m.size() - 1 && j == m[0].size() - 1) break;
      if (up) {
        row = i - 1;
        col = j + 1;
        badRow = row < 0;
        badCol = col >= m[0].size();
        if (badRow && badCol) {
          ++i;
          up = false;
          continue;
        }
        if (badRow) {
          ++j;
          up = false;
          continue;
        }
        if (badCol) {
          ++i;
          up = false;
          continue;
        }
        i = row;
        j = col;
        continue;
      }
      row = i + 1;
      col = j - 1;
      badRow = row >= m.size();
      badCol = col < 0;
      if (badRow && badCol) {
        ++j;
        up = true;
        continue;
      }
      if (badRow) {
        ++j;
        up = true;
        continue;
      }
      if (badCol) {
        ++i;
        up = true;
        continue;
      }
      i = row;
      j = col;
    }
    return result;
  }

  vector<int> findDiagonalOrder(vector<vector<int>>& mat) {
    m = move(mat);
    return f();
  }
};

/*

00 01 02 03
10 11 12 13
20 21 22 23
30 31 32 33

00 01 02
10 11 12
20 21 22

*/
