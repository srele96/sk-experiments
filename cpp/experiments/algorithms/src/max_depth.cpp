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

class Solution {
 public:
  int result = 0;

  void solve(TreeNode *node, int depth = 1) {
    if (node != nullptr) {
      solve(node->left, depth + 1);
      result = max(result, depth);
      solve(node->right, depth + 1);
      result = max(result, depth);
    }
  }

  int maxDepth(TreeNode *root) {
    solve(root);
    return result;
  }
};
