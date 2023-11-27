#include <bits/stdc++.h>
using namespace std;

namespace path {

namespace topDown {

vector<int> solve(const vector<vector<int>>& grid) {
  vector<vector<vector<int>>> dp(grid.size(),
                                 vector<vector<int>>(grid[0].size()));

  function<vector<int>(int, int)> cheapestPath = [&](int i = 0,
                                                     int j = 0) -> vector<int> {
    if (i == grid.size() - 1 && j == grid[i].size() - 1) {
      return {grid[i][j]};
    }

    if (dp[i][j].size() > 0) {
      return dp[i][j];
    }

    vector<int> down;
    if (i + 1 < grid.size()) {
      down = cheapestPath(i + 1, j);
    } else {
      down = {numeric_limits<int>::max()};
    }

    vector<int> right;
    if (j + 1 < grid[i].size()) {
      right = cheapestPath(i, j + 1);
    } else {
      right = {numeric_limits<int>::max()};
    }

    int downSum = 0, rightSum = 0;
    for (const int n : down) downSum += n;
    for (const int n : right) rightSum += n;

    if (downSum < rightSum) {
      down.insert(down.begin(), grid[i][j]);
      dp[i][j] = down;
      return dp[i][j];
    } else {
      right.insert(right.begin(), grid[i][j]);
      dp[i][j] = right;
      return dp[i][j];
    }
  };

  return cheapestPath(0, 0);
}

}  // namespace topDown

namespace bottomUp {

vector<int> solve(const vector<vector<int>>& grid) {
  vector<vector<vector<int>>> dp(grid.size(),
                                 vector<vector<int>>(grid[0].size()));

  function<vector<int>(int, int)> cheapestPath{
      [&](int i, int j) -> vector<int> {
        return {0};  //
      }};

  return cheapestPath(0, 0);
}

}  // namespace bottomUp

}  // namespace path

namespace sum {

int solve(const vector<vector<int>>& grid) {
  vector<vector<int>> dp(
      grid.size(), vector<int>(grid[0].size(), numeric_limits<int>::max()));

  function<int(int, int)> cheapestPath = [&](int i, int j) {
    if (i == grid.size() - 1 && j == grid[i].size() - 1) {
      return grid[i][j];
    }

    if (dp[i][j] != numeric_limits<int>::max()) {
      return dp[i][j];
    }

    int rightSum = i + 1 < grid.size() ? cheapestPath(i + 1, j)
                                       : numeric_limits<int>::max();
    int downSum = j + 1 < grid[i].size() ? cheapestPath(i, j + 1)
                                         : numeric_limits<int>::max();

    dp[i][j] = min(grid[i][j] + rightSum, grid[i][j] + downSum);
    return dp[i][j];
  };

  return cheapestPath(0, 0);
}

}  // namespace sum

int main() {
  vector<vector<vector<int>>> grids{
      {
          {1, 3, 1},  //
          {2, 5, 1},  //
          {4, 2, 1},
      },  //
      {
          {1, 2, 3},   //
          {1, 4, 5},   //
          {1, 1, 10},  //
      },               //
      {
          {1, 3, 5},   //
          {55, 1, 5},  //
          {10, 1, 1},  //
      },               //
  };

  for (const vector<vector<int>>& grid : grids) {
    for (const int n : path::topDown::solve(grid)) cout << n << " ";

    cout << "\n";

    for (const int n : path::bottomUp::solve(grid)) cout << n << " ";

    cout << "\n";

    cout << sum::solve(grid);

    cout << "\n";
  }

  return 0;
}
