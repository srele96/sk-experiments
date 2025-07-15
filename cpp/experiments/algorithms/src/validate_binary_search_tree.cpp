#include <functional>
using namespace std;

// https://leetcode.com/problems/validate-binary-search-tree/

// i should have solved this problem before trying to find a K size binary
// search tree within another binary tree because that problem uses the solution
// to this problem but thankfully to that i could solve this problem much faster
// and i wouldn't have been able to do it before
// not as fast at least...

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
  bool isValidBST(TreeNode *root) {
    bool result = true;
    struct minMax {
      double min;
      double max;
    };
    function<minMax(TreeNode *)> solve{[&result, &solve](TreeNode *node) {
      if (node == nullptr) {
        return minMax{2e32, -2e32};
      };
      minMax left = solve(node->left);
      minMax right = solve(node->right);

      if (left.max >= node->val || right.min <= node->val) {
        result = false;
      }

      minMax res;
      res.min = node->left != nullptr ? left.min : node->val;
      res.max = node->right != nullptr ? right.max : node->val;

      return res;
    }};
    solve(root);
    return result;
  }
};

}  // namespace a

namespace b {

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
  bool isValidBST(TreeNode *root) {
    function<bool(TreeNode *, double, double)> solve{
        [&](TreeNode *node, double minimum, double maximum) {
          if (node == nullptr) return true;
          // the difficulty is where to keep the maximum and minimum value of
          // the binary search tree initially that value should be out of range
          // of the problem's constraints
          if (minimum >= node->val || maximum <= node->val) return false;
          // maximum in the left subtree should be the current node
          // minimum in the right subtree should be the current node
          return solve(node->left, minimum, node->val) &&
                 solve(node->right, node->val, maximum);
        }};
    return solve(root, -2e32, 2e32);
  }
};

}  // namespace b
