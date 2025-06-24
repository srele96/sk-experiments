#include <bits/stdc++.h>
using namespace std;

// https://leetcode.com/problems/unique-binary-search-trees/?envType=problem-list-v2&envId=dynamic-programming

class Solution {
 public:
  int numTrees(int n) {
    array<int, 20> dp;
    dp.fill(-1);
    dp[0] = 1;
    dp[1] = 1;
    function<int(int)> f = [&](int node) {
      // Cache is absolutely required to avoid TLE
      if (dp[node] != -1) return dp[node];
      if (node == 0) return 1;
      if (node == 1) return 1;
      int s = 0;
      for (int i = 0; i < node; ++i) {
        // Notice that the two loops to construct the BST
        // Are a product
        // each left needs to be combined with each right subtree + r00t
        // There you go...
        s += f(i) * f(node - i - 1);
      }
      return dp[node] = s;
    };
    int r = f(n);
    for (int v : dp) {
      cout << v << ", ";
    }
    return r;
  }
};

namespace tleDoesNotCutIt {

class Solution {
 public:
  int numTrees(int n) {
    vector<vector<int>> dp(n + 1);
    function<vector<int>(int)> f = [&](int node) -> vector<int> {
      if (dp[node].size() > 0) return dp[node];
      if (node == 0) return {0};
      if (node == 1) return {1};
      vector<int> result;
      for (int i = 0; i < node; ++i) {
        for (auto right : f(node - i - 1)) {
          for (auto left : f(i)) {
            result.emplace_back(1);
          }
        }
      }
      return dp[node] = result;
    };

    return f(n).size();
  }
};

}  // namespace tleDoesNotCutIt
