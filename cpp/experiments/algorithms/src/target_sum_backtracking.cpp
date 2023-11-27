class Solution {
 public:
  void bt(vector<int>& nums, int target, int& result, int sum = 0, int i = 0) {
    if (i == nums.size()) {
      if (sum == target) ++result;
    } else {
      bt(nums, target, result, sum + nums[i], i + 1);
      bt(nums, target, result, sum - nums[i], i + 1);
    }
  }

  int findTargetSumWays(vector<int>& nums, int target) {
    int result = 0;
    bt(nums, target, result);
    return result;
  }
};
