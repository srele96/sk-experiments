#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
  int val;

  TreeNode* left;
  TreeNode* right;

  TreeNode();
  TreeNode(int val);
  TreeNode(int val, TreeNode* left, TreeNode* right);
};

TreeNode* bfs(TreeNode*, int, queue<TreeNode*>&);

struct FindVal {
  void operator()(TreeNode*, int, ostream&);
};

int main() {
  TreeNode* r{new TreeNode{1, new TreeNode{2, new TreeNode{8}, new TreeNode{4}},
                           new TreeNode{5, nullptr, new TreeNode{11}}}};

  for (auto val : {5, 99, 11}) FindVal{}(r, val, cout);

  return 0;
}

TreeNode::TreeNode() : val{0}, left{nullptr}, right{nullptr} {}
TreeNode::TreeNode(int val) : val{val}, left{nullptr}, right{nullptr} {}
TreeNode::TreeNode(int val, TreeNode* left, TreeNode* right)
    : val{val}, left{left}, right{right} {}

TreeNode* bfs(TreeNode* n, int val, queue<TreeNode*>& q) {
  if (n->val == val) return n;
  if (n->left != nullptr) q.push(n->left);
  if (n->right != nullptr) q.push(n->right);
  if (!q.empty()) {
    TreeNode* t{q.front()};
    q.pop();
    return bfs(t, val, q);
  }
  return nullptr;
}

void FindVal::operator()(TreeNode* r, int val, ostream& os) {
  queue<TreeNode*> q;
  TreeNode* res{bfs(r, val, q)};

  if (res != nullptr) {
    os << "Found: " << res->val << "\n";
  } else {
    os << "Not found: " << val << "\n";
  }
}
