#include <bits/stdc++.h>
using namespace std;

// https://leetcode.com/problems/flood-fill/

class Solution {
 public:
  // complex number to get up, right, down, left
  vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc,
                                int color) {
    vector<vector<bool>> visited(image.size(),
                                 vector<bool>(image[0].size(), false));
    function<void(int, int)> solve{[&](int i, int j) {
      if (visited[i][j]) return;
      visited[i][j] = true;
      // cout << i << ", " << j << "\n";
      // if the current pixel and top pixel are the same, flood top pixel
      if (i + 1 < image.size() && image[i][j] == image[i + 1][j]) {
        solve(i + 1, j);
        // image[i + 1][j] = color;
      }
      if (i - 1 >= 0 && image[i][j] == image[i - 1][j]) {
        solve(i - 1, j);
        // image[i - 1][j] = color;
      }
      if (j + 1 < image[i].size() && image[i][j] == image[i][j + 1]) {
        solve(i, j + 1);
        // image[i][j + 1] = color;
      }
      if (j - 1 >= 0 && image[i][j] == image[i][j - 1]) {
        solve(i, j - 1);
        // image[i][j - 1] = color;
      }

      image[i][j] = color;
    }};

    // if current and top are same, flood top
    // if current and right are same, flood right
    // if current and down are same, flood down
    // if current and left are same, flood left

    solve(sr, sc);

    return image;
  }
};
