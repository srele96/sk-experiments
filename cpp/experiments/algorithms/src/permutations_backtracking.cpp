#include <bits/stdc++.h>
using namespace std;

class Solution {
 private:
  void backtrack(vector<vector<int>>& answer, const vector<int>& nums,
                 vector<int> current = {}) {
    if (current.size() == nums.size()) {
      answer.push_back(current);
    }
    for (const auto& n : nums) {
      if (find(current.begin(), current.end(), n) == current.end()) {
        current.push_back(n);
        backtrack(answer, nums, current);
        current.pop_back();
      }
    }
  }

 public:
  vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> answer;
    backtrack(answer, nums);
    return answer;
  }
};

int main() {
  vector<int> nums = {1, 2, 3};

  Solution s;

  auto answer = s.permute(nums);
  for (const auto& a : answer) {
    for (const auto& n : a) {
      cout << n << " ";
    }
    cout << endl;
  }

  return 0;
}
