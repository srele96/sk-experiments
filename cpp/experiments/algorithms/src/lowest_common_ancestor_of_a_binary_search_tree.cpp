// can not put the recurrence relation, why?

// node > p
// node > q
// -> left
//
// node < p
// node < q
// -> right
//
// node is the value (wtf?)

// if root is bigger than both, left is answer
// if root is smaller than both, right is answer
// the current node is what we're looking for

// we do not look for the two nodes -> we do not search for both of them
//
// the search is all that i was familiar with so i jumped to conclusion that i
// have to find both values

// i had partial idea
// > bfs
// > check if node is one of values and search for the other value

// accepted solution take advantage of the balanced search tree property
// > left are smaller values
// > right are larger values

// i failed to read recurrence relation properly
// root smaller? go right
// root larger? go left
// root is answer
//
// if root is mid val, it's ancestor

// somewhere in my thoughts that was the short-circuited thought that there's
// split between two nodes however there were no further ideas regarding that
// one so it was discarded in a blink of an eye

// we search for the moment current node is between the two values -> core idea

// -----------------------------------------------------------------------------
// https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-search-tree/
// -----------------------------------------------------------------------------

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
 public:
  TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    // three cases
    // the root is ancestor of it's children
    // left is the ancestor of some of it's children
    // right is the ancestor of some of it's children
    //
    // ------------- post solution -----------
    // i got the initial idea right that there are tree cases
    // however i absolutely failed to notice some other properties
    // that tell me how to setup recurrence relation
    if (root->val > p->val && root->val > q->val) {
      return lowestCommonAncestor(root->left, p, q);
    }
    if (root->val < p->val && root->val < q->val) {
      return lowestCommonAncestor(root->right, p, q);
    }
    return root;
  }
};
