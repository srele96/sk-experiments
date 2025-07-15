#include <bits/stdc++.h>
using namespace std;

// https://leetcode.com/problems/binary-tree-zigzag-level-order-traversal/submissions/

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
  vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
    // I didn't read constraints of the problem and i didn't initially handle
    // the nullptr root, i should not carelessly solve problems regardless of
    // the problem constraints...
    //
    // i also feel like my previous attempts to understand a problem by
    // generating various cases was kind of similar to the problem solving stage
    // of the problem, but i think i got it all mixed up or some shit
    //
    // again i solved a problem that takes in the combination of two solutions,
    // this one solves level order traversal where i have to collect nodes in a
    // level order, but i did not know how to separate nodes by level, i knew
    // how to iterate but i did not know how to distinguish levels during
    // breadth first search, but now i do!

    if (root == nullptr) return {};

    queue<TreeNode*> q;
    q.push(root);
    vector<vector<int>> result;
    int level = 0;
    while (!q.empty()) {
      int _size = q.size();
      vector<int> row(_size);
      for (int i = 0; i < _size; ++i) {
        TreeNode* node = q.front();
        q.pop();
        row[i] = node->val;
        if (node->left != nullptr) q.push(node->left);
        if (node->right != nullptr) q.push(node->right);
      }
      if (level % 2 != 0) reverse(row.begin(), row.end());
      ++level;
      result.push_back(move(row));
    }

    return result;
  }
};

void solve(TreeNode*& node) {
  queue<TreeNode*> q;
  q.push(node);
  int level = 0;
  while (!q.empty()) {
    // why does breadth first search contains the size of the nodes for the
    // current level to visit, however the problem is that it also has sizes
    // between the current and next level, as we iterate through nodes on the
    // current level

    // clever, we know that we will have that many values, for that many times
    // we can pop value and push it's children to the stack, after which we
    // iterate over the next level, this solution is suitable for the symmetric
    // nodes check

    // it is an absolute must to calculate queue size only once outside of loop
    // condition `i < sz` because if we call `i < q.size()` inside the for loop,
    // each loop iteration may increase the queue size, so we end up iterating
    // incorrectly
    int sz = q.size();

    // why did i not notice earlier when i realized breadth first search can be
    // used to iterate over levels, how to keep info of the level, i did not
    // notice that i could use a for loop here, and that at start of each level
    // we know the size of the current level
    // i guess i did not notice that because i never laid out numerical
    // information during and after breadth first search iterations
    // that may or may not have generated information that i need, but it could
    // have been a nice exercise
    for (int i = 0; i < sz; ++i) {
      TreeNode* n = q.front();
      cout << n->val << ", ";

      q.pop();

      if (n->left != nullptr) q.push(n->left);
      if (n->right != nullptr) q.push(n->right);
    }

    cout << "\n";

    ++level;
  }
}

int main() {
  TreeNode* root = new TreeNode{
      1,  //
      new TreeNode{
          2,  //
          new TreeNode{
              4,                //
              new TreeNode{8},  //
              new TreeNode{9}   //
          },                    //
          new TreeNode{
              5,                 //
              new TreeNode{10},  //
              new TreeNode{11},  //
          },                     //
      },
      new TreeNode{
          3,  //
          new TreeNode{
              6,                 //
              new TreeNode{12},  //
              new TreeNode{13},  //
          },                     //
          new TreeNode{
              7,                 //
              new TreeNode{14},  //
              new TreeNode{15},  //
          },                     //
      },
  };

  solve(root);

  return 0;
}
