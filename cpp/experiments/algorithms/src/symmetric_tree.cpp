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
  bool isSymmetric(TreeNode* root) {
    function<bool(TreeNode*, TreeNode*)> solve{[&](TreeNode* left,
                                                   TreeNode* right) {
      if (left == nullptr || right == nullptr) {
        // ah so basically both must be null at the end, and if either is null,
        // we protect ourselves against accessing value of nullptr, we basically
        // want both to be nullptr at the end to indicate end = true, but if
        // only one is nullptr and other one isn't the we indicate end = false
        // because we check two different values?
        return left == right;  // Why?
      }
      if (left->val != right->val) return false;
      return solve(left->left, right->right) && solve(left->right, right->left);
    }};
    return solve(root->left, root->right);
  }
};

void dfs(TreeNode* node) {
  queue<TreeNode*> q;
  q.push(node);
  while (!q.empty()) {
    TreeNode* n = q.front();
    q.pop();
    cout << n->val << "\n";
    if (n->left != nullptr) q.push(n->left);
    if (n->right != nullptr) q.push(n->right);
  }
}

/*

-------------------------------------------------------------------------------

it is of the essence to generate many ways to look at the problem, the problem
is when i don't know of any ways to generate to look at the problem, if i
described the problem as two trees and noticed that i check left node against
right node and right node against left node, i would have been able to notice
something --- maybe i would have been able to notice something

i think the thing about trees is to notice some minimal repeating pattern which
helps me define recursion

-------------------------------------------------------------------------------

i was supposed to observe the recursion as left and right tree

left       right
  1          1
 / \        / \
1   1      1   1

|------------------------------|
| left tree    |    right tree |
|------------------------------|
| left node    |    right node |
| right node   |    left node  |
|------------------------------|

*/

int main() {
  /*

              1
          /     \
         1       1
       /  \     /   \
      1    2   2     1
     /\   /\   /\    /\
    1 2  3 4  4 3   2 1

  */

  TreeNode* root = new TreeNode{
      1,  //
      new TreeNode{
          1,  //
          new TreeNode{
              1,                //
              new TreeNode{1},  //
              new TreeNode{2}   //
          },                    //
          new TreeNode{
              2,                //
              new TreeNode{3},  //
              new TreeNode{4},  //
          },                    //
      },
      new TreeNode{
          1,  //
          new TreeNode{
              2,                //
              new TreeNode{4},  //
              new TreeNode{3},  //
          },                    //
          new TreeNode{
              1,                //
              new TreeNode{2},  //
              new TreeNode{1},  //
          },                    //
      },
  };

  dfs(root);
  cout << (Solution{}.isSymmetric(root) ? "yes" : "no");

  return 0;
}
