#include <algorithm>
#include <queue>
#include <vector>
using namespace std;

// https://leetcode.com/problems/binary-tree-level-order-traversal-ii/

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
  vector<vector<int>> levelOrderBottom(TreeNode *root) {
    // the idea is to use the level order traversal and simply reverse the
    // result
    //
    // can use any of the binary tree level order traversals:
    // - recursive
    // - queue
    // - stack
    // - some other...
    if (root == nullptr) return {};

    vector<vector<int>> result;
    queue<TreeNode *> q;
    q.push(root);
    while (!q.empty()) {
      int sz = q.size();
      vector<int> level(sz);
      for (int i = 0; i < sz; ++i) {
        TreeNode *node = q.front();
        q.pop();
        if (node->left != nullptr) q.push(node->left);
        if (node->right != nullptr) q.push(node->right);
        level[i] = node->val;
      }
      result.push_back(level);
    }
    reverse(result.begin(), result.end());
    return result;
  }
};
