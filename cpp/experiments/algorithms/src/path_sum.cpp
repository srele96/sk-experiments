#include <functional>
using namespace std;

// https://leetcode.com/problems/path-sum/

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
  bool hasPathSum(TreeNode* root, int targetSum) {
    bool result = false;
    // the idea is to use the recursion parameter with dfs which is root-to-leaf
    // traversal the parameter holds the sum so far combined with dfs is perfect
    // match
    function<void(TreeNode*, int)> dfs{[&](TreeNode* node, int sum) {
      // this protects us against the case where the root is null, the result
      // remains false
      if (node != nullptr) {
        dfs(node->left, sum + node->val);
        dfs(node->right, sum + node->val);
        // this check can be anywhere within `if (node != nullptr)` because of
        // the check if the current node is a leaf node

        // the problem is how do we make sure we check only leaf nodes
        // leaf node is the node without any children
        if (node->left == nullptr && node->right == nullptr) {
          if (node->val + sum == targetSum) {
            result = true;
          }
        }
      }
    }};
    dfs(root, 0);
    return result;
  }
};
