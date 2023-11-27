#include <bits/stdc++.h>
using namespace std;

int main() {
  vector<int> nums{1, 2, 3, 4, 5, 6};
  vector<vector<int>> result;

  function<void(vector<int>)> backtrack{
      [&nums, &result, &backtrack](vector<int> perm) {
        if (perm.size() == 2) {
          result.push_back(perm);
          return;
        }
        for (const int n : nums) {
          if (find(perm.begin(), perm.end(), n) == perm.end()) {
            perm.push_back(n);
            backtrack(perm);
            perm.pop_back();
          }
        }
      }};

  backtrack({});

  for (auto& v : result) {
    for (auto& n : v) {
      cout << n << " ";
    }
    cout << endl;
  }
}
