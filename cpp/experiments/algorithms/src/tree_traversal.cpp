#include <bits/stdc++.h>
using namespace std;

struct Node {
  int value;
  unique_ptr<Node> left;
  unique_ptr<Node> right;

  Node() : value{0} {}
  Node(int _value) : value{_value} {}
  Node(int _value, unique_ptr<Node> _left, unique_ptr<Node> _right)
      : value{_value}, left{move(_left)}, right{move(_right)} {}
};

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// The only difference was the location of the operation...
//
// The name literally describes it!
//
// Inorder: Operation is between the two child recursive calls.
// Preorder: Operation is before the two child recursive calls.
// Postorder: Operation is after the two child recursive calls.
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void inorder(const unique_ptr<Node>& node, ostream& os) {
  if (node == nullptr) return;

  inorder(node->left, os);
  os << node->value << "\n";
  inorder(node->right, os);
}

void preorder(const unique_ptr<Node>& node, ostream& os) {
  if (node == nullptr) return;

  os << node->value << "\n";
  preorder(node->left, os);
  preorder(node->right, os);
}

void postorder(const unique_ptr<Node>& node, ostream& os) {
  if (node == nullptr) return;

  postorder(node->left, os);
  postorder(node->right, os);
  os << node->value << "\n";
}

int main() {
  vector<unique_ptr<Node>> roots;

  roots.push_back(  //
      make_unique<Node>(
          15,
          make_unique<Node>(  //
              2,
              make_unique<Node>(5),  //
              make_unique<Node>(
                  6,
                  make_unique<Node>(7),  //
                  make_unique<Node>(8,
                                    make_unique<Node>(9),  //
                                    make_unique<Node>(10,
                                                      nullptr,  //
                                                      make_unique<Node>(1))))),
          make_unique<Node>(11,
                            make_unique<Node>(12),  //
                            nullptr)));

  roots.push_back(  //
      make_unique<Node>(1,
                        make_unique<Node>(2),  //
                        make_unique<Node>(3)));

  for (const unique_ptr<Node>& root : roots) {
    cout << "--------\n"
         << "Inorder:\n";
    inorder(root, cout);
    cout << "Preorder:\n";
    preorder(root, cout);
    cout << "Postorder:\n";
    postorder(root, cout);
  }

  return EXIT_SUCCESS;
}
