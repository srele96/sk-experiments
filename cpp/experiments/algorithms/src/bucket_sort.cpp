#include <bits/stdc++.h>
using namespace std;

/*



*/

int main() {
  vector<int> second{1, 2, 3, 4, 5, 6};
  vector<int> first{8, 9, 10, 11};

  first.insert(first.end(), second.begin(), second.end());

  for (auto i : first) {
    cout << i << " ";
  }

  cout << "\n\n-------------------\n\n";

  vector<int> nums{1, 1, 1, 2, 2, 3, 4, 6, 6, 5, 6};
  int k{2};
  unordered_map<int, int> freq;

  for (auto i : nums) {
    ++freq[i];
  }

  vector<vector<int>> buckets(nums.size() + 1);

  for (auto i : freq) {
    buckets[i.second].push_back(i.first);
  }

  for (auto it{buckets.rbegin()}; it != buckets.rend(); ++it) {
    if (!it->empty()) {
      for (auto i : *it) {
        cout << i << " ";
      }
      cout << "\n";
    }
  }

  cout << "\n\n-------------------\n\n";

  vector<int> res;
  for (auto it{buckets.rbegin()}; it != buckets.rend() && res.size() < k;
       ++it) {
    if (!it->empty()) {
      res.insert(res.end(), it->begin(), it->end());
    }
  }

  for (auto i : res) {
    cout << i << " ";
  }

  return 0;
}
