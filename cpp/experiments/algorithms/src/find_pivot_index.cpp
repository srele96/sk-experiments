#include <vector>
using namespace std;

// the idea was to use prefix and postfix array to find such index in O(n) time
// and O(n) memory

// https://leetcode.com/problems/find-pivot-index/

class Solution {
 public:
  int pivotIndex(vector<int>& nums) {
    int n = nums.size();
    vector<int> prefix(n);
    vector<int> postfix(n);
    prefix[0] = nums[0];
    for (int i = 1; i < n; ++i) {
      prefix[i] = prefix[i - 1] + nums[i];
    }
    postfix[n - 1] = nums[n - 1];
    for (int i = n - 2; i >= 0; --i) {
      postfix[i] = postfix[i + 1] + nums[i];
    }
    int idx = -1;
    for (int i = 0; i < n; ++i) {
      int left = i > 0 ? prefix[i - 1] : 0;
      int right = i < n - 1 ? postfix[i + 1] : 0;
      if (left == right) {
        idx = i;
        break;
      }
    }
    return idx;
  }
};
