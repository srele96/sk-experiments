#include <functional>
#include <unordered_map>
#include <vector>

using namespace std;

// This shit took me around 10 hours to solve by myself with 2 hints:
// - 2 recursive calls
// - a digit per recursion call
// and i used a whole notebook figuring out how do those digits play together

// https://leetcode.com/problems/all-possible-full-binary-trees/

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
  vector<TreeNode *> allPossibleFBT(int n) {
    if (n % 2 == 0) return {};

    unordered_map<int, vector<TreeNode *>> dp;
    function<vector<TreeNode *>(int)> solve{
        [&solve, &dp](int n) -> vector<TreeNode *> {
          if (n == 1) return dp[n] = {new TreeNode{}};

          if (dp.count(n) != 0) return dp[n];

          vector<TreeNode *> result;
          int l = n, r = 1;

          while (l >= 1) {
            for (auto &left : solve(l - 2))
              for (auto &right : solve(r)) {
                TreeNode *root = new TreeNode{};
                root->left = left;
                root->right = right;
                result.push_back(root);
              }

            l -= 2;
            r += 2;
          }

          return dp[n] = result;
        }};

    return solve(n);
  }
};
