#include <vector>

using namespace std;

// - can't run ahead of myself if i don't have something in my permanent memory
// to rely on
// - i never considered using two pointers `left, right` to achieve O(n) runtime
// -
// -

namespace a {

// Good. My O(n^2) solution reached TLE on the first run as expected.

class Solution {
 public:
  int maxArea(vector<int>& height) {
    int mostWaterSize = 0;

    for (int i = 1; i < height.size(); ++i) {
      for (int j = 0; j < i; ++j) {
        int distance = i - j;
        int waterSize = distance * min(height[i], height[j]);
        if (waterSize > mostWaterSize) {
          mostWaterSize = waterSize;
        }
      }
    }

    return mostWaterSize;
  }
};

}  // namespace a

namespace b {

// Understand, absorb, and copy the solution proposed in discussion.
class Solution {
 public:
  int maxArea(vector<int>& height) {
    int left = 0, right = height.size() - 1, _maxArea = 0;

    while (left < right) {
      int area = (right - left) * min(height[left], height[right]);
      if (area > _maxArea) _maxArea = area;

      if (height[left] < height[right]) {
        ++left;
      } else {
        --right;
      }
    }

    // for(int i = 1; i < height.size(); ++i) {
    //     // dist furthest left with >= height[i]
    //     for(int j = 0; j < i; ++j) {
    //         >= height[i]
    //         int distance = i - j;
    //         int waterSize = distance * min(height[i], height[j]);
    //         if (waterSize > mostWaterSize) {
    //             mostWaterSize = waterSize;
    //         }
    //     }
    // }

    return _maxArea;
  }
};

}  // namespace b
