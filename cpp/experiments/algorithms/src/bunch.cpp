#include <bits/stdc++.h>
using namespace std;

// no idea what i did here

namespace a {
class Solution {
 public:
  int removeDuplicates(vector<int>& nums) {
    int pos = 0, k = 0;
    unordered_set<int> s;
    for (int i = 0; i < nums.size(); ++i) {
      if (s.find(nums[i]) == s.end()) {
        s.insert(nums[i]);
        int tmp = nums[pos];
        nums[pos] = nums[i];
        nums[i] = tmp;
        ++pos;
        ++k;
      }
    }
    return k;
  }
};
}  // namespace a

namespace b {
class Solution {
 public:
  int removeDuplicates(vector<int>& nums) {
    int pos = 0, k = 0;
    unordered_set<int> s;
    for (int i = 0; i < nums.size(); ++i) {
      if (s.find(nums[i]) == s.end()) {
        s.insert(nums[i]);
        nums[pos] = nums[i];
        ++pos;
        ++k;
      }
    }
    return k;
  }
};
}  // namespace b

namespace c {
class Solution {
 public:
  int removeDuplicates(vector<int>& nums) {
    int c = 0;
    for (int i = 1; i < nums.size(); ++i) {
      if (nums[i] == nums[i - 1]) {
        ++c;
      } else {
        nums[i - c] = nums[i];
      }
    }
    return nums.size() - c;
  }
};

}  // namespace c

namespace d {

class Solution {
 public:
  int searchInsert(vector<int>& nums, int target) {
    int l = 0, r = nums.size() - 1, p = (l + r) / 2, pos = p;

    while (l < r) {
      p = (l + r) / 2;
      if (target > nums[p]) {
        l = p + 1;
      } else if (target < nums[p]) {
        r = p - 1;
      } else {
        return p;
      }
    }
    // index where it would be inserted
    return nums[l] < target ? l + 1 : l;
  }
};

}  // namespace d

namespace e {

class Solution {
 public:
  int searchInsert(vector<int>& nums, int target) {
    int l = 0, r = nums.size() - 1, p = (l + r) / 2, pos = p;

    while (l <= r) {
      p = (l + r) / 2;
      if (target > nums[p]) {
        l = p + 1;
      } else if (target < nums[p]) {
        r = p - 1;
      } else {
        return p;
      }
    }
    // index where it would be inserted
    return l;
  }
};

}  // namespace e

namespace f {

//

}  // namespace f

int main() {
  vector<int> n{};
  int i = !n.empty();

  cout << i;
}
