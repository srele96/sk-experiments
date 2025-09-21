#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left),
 * right(right) {}
 * };
 */
class Solution {
 public:
  unordered_map<TreeNode *, unordered_map<bool, int>> dp;
  int dfs(TreeNode *n, bool canRob) {
    if (n == nullptr) return 0;
    if (dp.count(n) && dp[n].count(canRob)) return dp[n][canRob];

    if (canRob) {
      return dp[n][canRob] =
                 max(n->val + dfs(n->left, false) + dfs(n->right, false),
                     dfs(n->left, true) + dfs(n->right, true));
    }
    return dp[n][canRob] = dfs(n->left, true) + dfs(n->right, true);
  }
  int rob(TreeNode *root) { return dfs(root, true); }
};
