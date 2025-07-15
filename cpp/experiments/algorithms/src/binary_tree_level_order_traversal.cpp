#include <functional>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

// https://leetcode.com/problems/binary-tree-level-order-traversal/

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

namespace a {

class Solution {
 public:
  vector<vector<int>> levelOrder(TreeNode *root) {
    if (root == nullptr) return {};

    vector<vector<int>> result;
    queue<TreeNode *> q;
    q.push(root);
    while (!q.empty()) {
      int size = q.size();
      vector<int> level;
      for (int i = 0; i < size; ++i) {
        TreeNode *node = q.front();
        q.pop();
        if (node->left != nullptr) q.push(node->left);
        if (node->right != nullptr) q.push(node->right);
        level.push_back(node->val);
      }
      result.push_back(level);
    }
    return result;
  }
};

}  // namespace a

namespace b {

class Solution {
 public:
  vector<vector<int>> levelOrder(TreeNode *root) {
    vector<vector<int>> result;
    function<void(TreeNode *, int)> dfs{[&](TreeNode *node, int level) {
      if (node != nullptr) {
        dfs(node->left, level + 1);
        dfs(node->right, level + 1);
        if (result.size() < level + 1) {
          result.resize(level + 1);
        }
        result[level].push_back(node->val);
      }
    }};
    dfs(root, 0);
    return result;
  }
};

}  // namespace b

namespace c {

class Solution {
 public:
  vector<vector<int>> levelOrder(TreeNode *root) {
    if (root == nullptr) return {};

    vector<vector<int>> result;
    stack<pair<TreeNode *, int>> s;
    s.push({root, 0});
    while (!s.empty()) {
      pair<TreeNode *, int> node_p = s.top();
      s.pop();
      if (node_p.first->right != nullptr)
        s.push({node_p.first->right, node_p.second + 1});
      if (node_p.first->left != nullptr)
        s.push({node_p.first->left, node_p.second + 1});
      if (result.size() < node_p.second + 1) {
        result.resize(node_p.second + 1);
      }
      result[node_p.second].push_back(node_p.first->val);
    }
    return result;
  }
};

}  // namespace c

// possible implementations
// - Morris Traversal for Level Order
// - Two-Queue Approach
