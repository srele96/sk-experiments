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

/*

   7
 2   6
1 3 4 5

7
2
1
print(1)
2
print(2)
3
print(3)
7
print(7)
6
4
print(4)
6
print(6)
5
print(5)

second visit or leaf? ...


i observed that each printed node is visited twice except leafs so i created
a map that counts visits and condition to print current node if it is visited
twice or has no leafs, however


       3
     /  \
  null   2
        /
       1

yields incorrect results because print order is: 1 2 3, and for inorder it
should be: 3 1 2

i failed to see beyond the case that i handled

*/

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

  vector<int> inorderTraversal(TreeNode *root) {
    vector<int> result;
    unordered_set<TreeNode *> visited_node;
    unordered_map<TreeNode *, TreeNode *> previous_node;
    unordered_map<TreeNode *, int> visited_count;
    unordered_set<TreeNode *> used;

    TreeNode *current_node{root};

    while (current_node != nullptr) {
      ++visited_count[current_node];
      visited_node.insert(current_node);

      // Implementing in-order traversal here is non trivial because of how
      // recursive implementation works. Recursive implementation prints the
      // current node after returning from the next node. Leaf node value is
      // printed after it enters null value, then goes back and print leaf, then
      // goes back to parent and prints parent, enters right child, enters right
      // child left null, goes back from right child null and prints the right
      // child, goes back to parent, goes to parent's parent...
      //
      // Since the current iterative implementation builds up on top of behavior
      // of recursion and has straightforward way to do preorder and postorder,
      // however it doesn't mimic going to the next node and back. The
      // replacement for that is a map to keep track of parents of each node so
      // we can go to parent from any node at any point in time.
      //
      // Maybe potential in-order traversal can be implemented based on that
      // map? A node is printed once it goes back from the first node it
      // entered, however that behavior does not apply here. Also if we have no
      // left node, we print the current node. So maybe if current node is leaf
      // or visited twice or has no left child?
      //
      // I observed that properties of node that we should print are that it is
      // leaf, visited second time or has no left child, however any node that
      // has no left child would be printed more than once. Therefore we keep
      // track of the printed nodes...

      TreeNode *left{current_node->left};
      TreeNode *right{current_node->right};

      const bool is_leaf{left == nullptr && right == nullptr};
      const bool is_second_visit{visited_count[current_node] == 2};
      const bool has_no_left_child{left == nullptr};
      const bool should_use{is_leaf || is_second_visit || has_no_left_child};
      if (should_use && !used.count(current_node)) {
        used.insert(current_node);
        result.push_back(current_node->val);
      }

      if (left != nullptr && !visited_node.count(left)) {
        previous_node[left] = current_node;
        current_node = left;
      } else if (right != nullptr && !visited_node.count(right)) {
        previous_node[right] = current_node;
        current_node = right;
      } else {
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

  for (const int v : Iterative::Solution{}.inorderTraversal(root)) {
    cout << v << " ";
  }

  cout << "\n";

  return 0;
}
