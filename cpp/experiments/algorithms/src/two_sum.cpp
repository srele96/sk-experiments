#include <bits/stdc++.h>
using namespace std;

// https://leetcode.com/problems/two-sum/

class Solution {
 public:
  vector<int> twoSum(vector<int>& nums, int target) {
    map<int, int> seen;
    for (int i = 0; i < static_cast<int>(nums.size()); ++i) {
      if (auto s = seen.find(target - nums[i]); s != seen.end()) {
        return {i, seen[target - nums[i]]};
      }
      seen[nums[i]] = i;
    }
    return {};
  }
};
