#include <functional>
#include <vector>
using namespace std;

// https://leetcode.com/problems/path-sum-ii/

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
  vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
    // backtracking state, we utilize the idea of the path sum and backtracking
    // state we also utilize the backtracking property of depth-first-search
    // where we backtrack once we visit leaf node
    //
    // conceptually the recursion states:
    //
    // - collect the current nodes value
    // - do the same for left node
    // - do the same for right node
    // - undo the choice
    vector<int> state;
    vector<vector<int>> result;
    function<void(TreeNode*, int)> dfs{[&](TreeNode* node, int sum) {
      if (node != nullptr) {
        state.push_back(node->val);
        dfs(node->left, sum + node->val);
        dfs(node->right, sum + node->val);
        if (node->left == nullptr && node->right == nullptr) {
          if (sum + node->val == targetSum) {
            result.push_back(state);
          }
        }
        state.pop_back();
      }
    }};
    dfs(root, 0);
    return result;
  }
};
