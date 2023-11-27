#include <bits/stdc++.h>
using namespace std;

/*


1

[]
[1]


1 2

[]
[1]
[1 2] -> done
[1]
[]
[2]
[2 1] -> done


1 2 3

[]
[1]
[1 2]
[1 2 3] -> done
[1 2]
[1]
[1 3]
[1 3 2] -> done
[1 3]
[1]
[]
[2]
[2 1]
[2 1 3] -> done
[2 1]
[2]
[2 3]
[2 3 1] -> done
[2 3]
[2]
[]
[3]
[3 1]
[3 1 2] -> done
[3 1]
[3]
[3 2]
[3 2 1] -> done


1 2 3 4

[]
[1]
[1 2]
[1 2 3]
[1 2 3 4] -> done
[1 2 3]
[1 2]
[1 2 4]
[1 2 4 3] -> done
[1 2 4]
[1 2]
[1]
[1 3]
[1 3 2]
[1 3 2 4] -> done
[1 3 2]
[1 3]
[1 3 4]
[1 3 4 2] -> done
[1 3 4]
[1 3]
[1]
[1 4]
[1 4 2]
[1 4 2 3] -> done
[1 4 2]
[1 4]
[1 4 3]
[1 4 3 2] -> done
[1 4 3]
[1 4]
[1]
[]
[2]





for each number
  if number is not in current
    add it to the current
    backtrack to current
    remove the current







1 2

[]
for each number
  if number is not currently
    add it
    repeat for others
    remove it

1 2 3 4 5

[]
[1]
repeat for others
remove it


*/

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
