#include <bits/stdc++.h>
using namespace std;

// https://leetcode.com/problems/unique-binary-search-trees-ii/

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

namespace workingSolutionWorksWithoutCachingToo {

class Solution {
 public:
  TreeNode *clone(TreeNode *node) {
    if (node == nullptr) return nullptr;

    TreeNode *root = new TreeNode(node->val);
    root->left = clone(node->left);
    root->right = clone(node->right);
    return root;
  }

  vector<TreeNode *> generateTrees(int n) {
    // Improves the solution from beats 4% to beats 28% ...
    vector<unordered_map<int, vector<TreeNode *>>> dp(n + 1);

    function<vector<TreeNode *>(int, int)> f =
        [&](int node, int val) -> vector<TreeNode *> {
      if (dp[node].find(val) != dp[node].end()) {
        return dp[node][val];
      }
      if (node == 0) return {nullptr};
      if (node == 1) return {new TreeNode(val)};

      vector<TreeNode *> roots;

      // the choice of value at the current node matters
      // and the problem requires further analysis because
      // i don't know how would i choose the value at each node
      // i need to re-analyse the structures of each generated tree and
      // hence figure out where does the value choice on a node fit in
      // all nodes in the right subtree are larger than current node
      // all nodes in leftsubtree are smaller than current node

      for (int i = 0; i < node; ++i) {
        // I missed an important detail... The tree is BINARY SEARCH TREE
        // Where nodes in left subtree are < than current node
        // Where nodes in right subtree are > than current node
        // Notice a pattern that current node is smaller by amount of nodes in
        // the right subtree And the node in the left subtree is only 1 value
        // smaller than the current node
        int rightNodes = node - i - 1;
        for (auto right : f(rightNodes, val)) {
          for (auto left : f(i, val - rightNodes - 1)) {
            roots.emplace_back(
                new TreeNode(val - rightNodes, clone(left), clone(right)));
          }
        }
      }

      return dp[node][val] = roots;
    };

    return f(n, n);
  }
};

}  // namespace workingSolutionWorksWithoutCachingToo

namespace incompleteInitialSolution {

// class Solution {
//  public:
//   vector<TreeNode *> generateTrees(int n) {
//     function<vector<TreeNode *>(int)> f = [&](int c) -> vector<TreeNode *> {
//       if (c == 0) return {nullptr};
//       if (c == 1) return {new TreeNode(1)};
//       for (int i = 0; i < n; ++i) {
//         vector<TreeNode *> withRights;
//         for (auto rightNode : f(c - i - 1)) {
//           withRights.emplace_back(new TreeNode(c, nullptr, rightNode));
//         }
//         vector<TreeNode *> withLefts;
//         for (auto leftNode : f(i)) {
//           for (auto root : withRights) {
//             root->left = leftNode;
//           }
//         }
//       }
//     };
//   }
// };

}  // namespace incompleteInitialSolution
