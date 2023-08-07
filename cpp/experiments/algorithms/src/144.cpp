#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

namespace Recursive {

class Solution {
 public:
  vector<int> result;
  vector<int> preorderTraversal(TreeNode *root) {
    function<void(TreeNode *)> collect{[&](TreeNode *node) {
      if (node == nullptr) return;
      result.push_back(node->val);
      collect(node->left);
      collect(node->right);
    }};
    collect(root);
    return result;
  }
};

}  // namespace Recursive

namespace Iterative {

class Solution {
 public:
  vector<int> preorderTraversal(TreeNode *root) {
    vector<int> result;
    // Without marking nodes as visited we will go down the same tree more than
    // once and enter an infinite loop.
    unordered_set<TreeNode *> visited_node;
    // Recursion is chaotic and as we jump between nodes I couldn't think of
    // O(1) way to store the previous node of the current one. I assume the map
    // could be optimized by cleaning up nodes we do not need to keep track of
    // any more. Such nodes are whose both child nodes have been processed.
    unordered_map<TreeNode *, TreeNode *> previous_node;

    TreeNode *current_node{root};

    while (current_node != nullptr) {
      if (!visited_node.count(current_node)) {
        result.push_back(current_node->val);
      }
      visited_node.insert(current_node);

      TreeNode *left{current_node->left};
      TreeNode *right{current_node->right};
      if (left != nullptr && !visited_node.count(left)) {
        previous_node[left] = current_node;
        current_node = left;
      } else if (right != nullptr && !visited_node.count(right)) {
        previous_node[right] = current_node;
        current_node = right;
      } else {
        // Backtracking step which works regardless of the node we are currently
        // on.
        current_node = previous_node[current_node];
      }
    }

    return result;
  }
};

}  // namespace Iterative

int main() {
  TreeNode *root{//
                 new TreeNode{1,
                              new TreeNode{
                                  2,
                                  new TreeNode{4},
                                  new TreeNode{
                                      5,
                                      new TreeNode{6},
                                      new TreeNode{7},
                                  },
                              },
                              new TreeNode{
                                  3,
                                  new TreeNode{8},
                                  new TreeNode{9},
                              }}};

  for (const int v : Recursive::Solution{}.preorderTraversal(root)) {
    cout << v << " ";
  }

  cout << "\n";

  for (const int v : Iterative::Solution{}.preorderTraversal(root)) {
    cout << v << " ";
  }

  cout << "\n";

  return 0;
}
