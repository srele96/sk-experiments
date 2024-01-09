#include <functional>
#include <vector>

using namespace std;

// https://leetcode.com/problems/jump-game-ii/

namespace a {

class Solution {
 public:
  int jump(vector<int>& nums) {
    int end = nums.size() - 1;
    vector<int> cache(nums.size(), 10e5);
    cache[end] = 0;
    while (--end >= 0) {
      // for each possible jump from the cell
      for (int i = nums[end]; i >= 0; --i) {
        if (end + i >= nums.size()) {  // if jump is directly to the end
          cache[end] = 1;
        } else {
          // we jumped to another cell
          cache[end] = min(cache[end], cache[end + i] + 1);
        }
      }
    }
    return cache[0];
  }
};

}  // namespace a

namespace b {

class Solution {
 public:
  int jump(vector<int>& nums) {
    vector<int> cache(nums.size(), 10e5);
    function<int(int)> minJumps{[&nums, &minJumps, &cache](int idx) {
      // min jumps from last or after last to last is 0
      if (idx >= nums.size() - 1) return 0;
      if (cache[idx] != 10e5) return cache[idx];
      // for each jump from current cell
      for (int jump = nums[idx]; jump > 0; --jump) {
        // if the jump to the next cell is more optimal the amount of jumps to
        // the current cell
        cache[idx] = min(cache[idx], minJumps(idx + jump) + 1);
      }
      return cache[idx];
    }};
    return minJumps(0);
  }
};

}  // namespace b
