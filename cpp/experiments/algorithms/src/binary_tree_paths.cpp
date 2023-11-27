#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val{0}, left{nullptr}, right{nullptr} {}
  TreeNode(int x) : val{x}, left{nullptr}, right{nullptr} {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val{x}, left{left}, right{right} {}
};

class Solution {
 public:
  void bt(TreeNode* n, vector<string>& r, vector<string>& c) {
    c.push_back(to_string(n->val));
    if (n->left != nullptr) bt(n->left, r, c);
    if (n->right != nullptr) bt(n->right, r, c);
    if (n->left == nullptr && n->right == nullptr)
      r.push_back(c.size() > 0
                      ? accumulate(next(c.begin()), c.end(), *c.begin(),
                                   [](const string& a, const string& b) {
                                     return a + "->" + b;
                                   })
                      : "");
    c.pop_back();
  }

  vector<string> binaryTreePaths(TreeNode* root) {
    vector<string> res, cur;
    bt(root, res, cur);
    return res;
  }
};

int main() {
  TreeNode* root{new TreeNode{1, new TreeNode{2, nullptr, new TreeNode{5}},
                              new TreeNode{3}}};
  for (auto& s : Solution{}.binaryTreePaths(root)) cout << s << "\n";
  return 0;
}
