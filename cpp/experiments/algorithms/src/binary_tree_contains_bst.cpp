#include <algorithm>
#include <functional>
#include <iostream>
#include <limits>
using namespace std;

// https://www.geeksforgeeks.org/check-if-the-binary-tree-contains-a-balanced-bst-of-size-k/

/*

self research notes

binary search tree
- height
- sorted
- balanced
  >> does balanced binary search tree exist within binary tree?

i have never done similar problem where i look for a part of the tree within a
tree nothing similar, there is nothing to use from my existing knowledge

1. postorder
2. notice we need to track properties
3. propagate properties as we traverse

1. notice traversal order
2. notice subproblems

if i knew that the valid binary search tree should either be the whole tree or
should start from leafs i might have spotted a pattern there... i might have...

1. left
2. right
3. root

1. right
2. left
3. root

how do we maintain sorted property of binary search tree?

how can we be sure left subtree contains smaller values than right subtree?
- smallest value of right subtree is larger than largest value of left subtree
- height of left subtree and right must differ by 0 or 1

- i discovered new way of thinking
  >> traverse recursively (pre, post, in - order)
  >> collect properties

  !!>> explore that idea further >> how else to use it?

- i did not know about property delegation
  >> sum of values in the tree

- i understood solutions once i understood sub-problems

- i generate instantly smaller ideas
  (left subtree has all values smaller than right subtree)

- bigger stuff i don't know
  for example
    >> i could not find the relationship between post-order traversal and
    solution

  >> i did not know how or if or when i could collect properties


>>>>>>>>>>>>>>>>>>>>>>>>>
!!! MISTAKE !!!
- once a subtree is discarded we can start calculation again

here i made a mistaken assumption that i discard one node if a subtree's is BST
but is not balanced!
>>>>>>>>>>>>>>>>>>>>>>>>>

three way thinking
  > base case
  > node
  > left
  > right
  > the whole tree

-------------------------------------------------------------------------------

in the end after iterating through their code in my mind i realized it won't
discard any nodes but instead because of height difference will render the whole
subtree as invalid, either left, right subtree, or the whole tree with the root
node

so we ended up having three possibilities:
- the left subtree satisfied K nodes
- the right subtree satisfies K nodes
- the left and right subtree with the root node satisfy the K nodes

*/

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

struct info {
  bool isBst;
  bool balanced;
  int size;
  int height;
  int min;
  int max;
};

info postorder(TreeNode *node, int k, bool &ans) {
  if (node == nullptr) {
    // default values for leaf node
    return info{
        true,
        true,
        0,
        0,
        numeric_limits<int>::max(),
        numeric_limits<int>::min(),
    };
  }

  info inf{};

  info lsTree = postorder(node->left, k, ans);
  if (ans) return inf;
  info rsTree = postorder(node->right, k, ans);
  if (ans) return inf;

  if (!lsTree.isBst || !rsTree.isBst || lsTree.max > node->val ||
      rsTree.min < node->val) {
    inf.isBst = false;
    return inf;
  }

  inf.balanced = abs(lsTree.height - rsTree.height) <= 1;
  inf.isBst = true;
  inf.size = 1 + lsTree.size + rsTree.size;
  inf.height = 1 + max(lsTree.height, rsTree.height);
  inf.min = node->left != nullptr ? lsTree.min : node->val;
  inf.max = node->right != nullptr ? rsTree.max : node->val;

  if (inf.balanced && inf.size == k) ans = true;

  return inf;
}

void solve(TreeNode *node, int k) {
  bool ans = false;
  info inf = postorder(node, k, ans);

  cout << (ans ? "YES" : "NO");
}

void traverse_postorder(TreeNode *node, const function<void(TreeNode *)> &cb) {
  if (node == nullptr) {
    return;
  }
  traverse_postorder(node->left, cb);
  traverse_postorder(node->right, cb);
  cb(node);
}

int main() {
  /*

              10
             /  \
           6     25
         /  \    / \
        4  8   20   35
       /       /
      3       15
     /
    1

  */

  /*

  The algorithm doesn't work for the subtree:

        6
      / \
      4   8
    /
    3

  It doesn't discard one node, node 1, to detect a balanced binary search tree
  which is subtree of a binary tree

  That wasn't clarified on geeks for geeks page...

  I didn't understand all the input cases that I needed to handle to solve the
  problem, lesson learned, always, absolutely always, thoroughly check all the
  valid and invalid input cases before even touching a problem-solving stage

  once i started solving the problem i tried to traverse the tree from the leaf,
  but i didn't know what to do if a leaf leads to imbalanced tree, such as leaf
  number 1

  i thought i understood the requirements of the problem and i generated various
  structures of the binary tree and balanced binary search tree, however i did
  not understand all valid variants of binary search tree within the binary tree

  */

  TreeNode *root = new TreeNode(10);
  root->left = new TreeNode(6);
  root->right = new TreeNode(25);
  root->left->left = new TreeNode(4);
  root->left->right = new TreeNode(8);
  root->left->left->left = new TreeNode(3);
  root->left->left->left->left = new TreeNode(1);
  root->right->left = new TreeNode(20);
  root->right->left->left = new TreeNode(15);
  root->right->right = new TreeNode(35);

  solve(root, 4);

  traverse_postorder(root, [](TreeNode *node) { delete node; });

  return 0;
}
