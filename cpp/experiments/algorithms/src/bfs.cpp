#include <bits/stdc++.h>
using namespace std;

// Recursive types in C++ require pointer because we don't know the size of the
// type at compile time.
// https://stackoverflow.com/questions/6517231/are-c-recursive-type-definitions-possible-in-particular-can-i-put-a-vectort
// https://learn.microsoft.com/en-us/cpp/c-language/incomplete-types?view=msvc-170
struct TreeNode {
  // A value must be before the recursive type declaration, otherwise compiler
  // complains. I got `-Wreorder` message.
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

class CleanUp {
 private:
  void m_collect_children(TreeNode*, queue<TreeNode*>&, deque<TreeNode*>&);

 public:
  void operator()(TreeNode*);
};

int main() {
  TreeNode* r{new TreeNode{
      1, new TreeNode{2, new TreeNode{8}, new TreeNode{4}},
      new TreeNode{5, nullptr, new TreeNode{11, nullptr, new TreeNode(15)}}}};

  for (auto val : {5, 99, 11, 15}) FindVal{}(r, val, cout);

  std::cout << "Size of recursive type TreeNode is: " << sizeof(TreeNode)
            << "\n"
            << "Size of int is: " << sizeof(int) << "\n";

  CleanUp{}(r);

  return 0;
}

TreeNode::TreeNode() : val{0}, left{nullptr}, right{nullptr} {}
TreeNode::TreeNode(int val) : val{val}, left{nullptr}, right{nullptr} {}
TreeNode::TreeNode(int val, TreeNode* left, TreeNode* right)
    : val{val}, left{left}, right{right} {}

TreeNode* bfs(TreeNode* n, int val, queue<TreeNode*>& q) {
  cout << "Currently on n->val: " << n->val << "\n";
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

void CleanUp::m_collect_children(TreeNode* n, queue<TreeNode*>& q,
                                 deque<TreeNode*>& out) {
  out.push_back(n);
  if (n->left != nullptr) q.push(n->left);
  if (n->right != nullptr) q.push(n->right);
  if (!q.empty()) {
    TreeNode* t{q.front()};
    q.pop();
    m_collect_children(t, q, out);
  }
}

void CleanUp::operator()(TreeNode* r) {
  queue<TreeNode*> q;
  deque<TreeNode*> deq;

  m_collect_children(r, q, deq);

  while (!deq.empty()) {
    TreeNode* n{deq.back()};
    cout << "Cleaning up n->val: " << n->val << "\n";
    delete n;
    deq.pop_back();
  }
}
