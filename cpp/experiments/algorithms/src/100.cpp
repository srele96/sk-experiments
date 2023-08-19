#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};

class Solution {
 public:
  bool result = true;

  void dfs(TreeNode* p, TreeNode* q) {
    if (p != nullptr || q != nullptr) {
      int pv = p == nullptr ? 10e5 : p->val;
      int qv = q == nullptr ? 10e5 : q->val;
      if (qv != pv) {
        result = false;
        return;
      }

      dfs(p->left, q->left);
      dfs(p->right, q->right);
    }
  }

  bool isSameTree(TreeNode* p, TreeNode* q) {
    dfs(p, q);
    return result;
  }
};
