#include <vector>
using namespace std;

// https://leetcode.com/problems/range-sum-query-immutable/

class NumArray {
 public:
  vector<int> prefix;
  NumArray(vector<int>& nums) {
    prefix = vector<int>(nums.size());
    prefix[0] = nums[0];
    for (int i = 1; i < prefix.size(); ++i) {
      prefix[i] = prefix[i - 1] + nums[i];
    }
  }

  int sumRange(int left, int right) {
    int sum = prefix[right];
    if (left > 0) sum -= prefix[left - 1];
    return sum;
  }
};
