#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  vector<vector<string>> groupAnagrams(vector<string>& strs) {
    unordered_map<string, vector<string>> groups;
    for (auto& s : strs) {
      string sorted = s;
      sort(sorted.begin(), sorted.end());
      groups[sorted].push_back(s);
    }
    vector<vector<string>> res;
    for (auto& [_, val] : groups) {
      res.push_back(val);
    }
    return res;
  }
};
