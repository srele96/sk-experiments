#include <cmath>
#include <vector>
using namespace std;

// https://leetcode.com/problems/minimum-value-to-get-positive-step-by-step-sum/

class Solution {
 public:
  int minStartValue(vector<int>& nums) {
    int n = nums.size();
    vector<int> prefix(n);
    prefix[0] = nums[0];
    int smallest = prefix[0];

    for (int i = 1; i < n; ++i) {
      prefix[i] = prefix[i - 1] + nums[i];
      if (prefix[i] < smallest) smallest = prefix[i];
    }
    if (smallest <= 0) {
      smallest = abs(smallest) + 1;
    } else {
      smallest = 1;
    }
    return smallest;
  }
};
