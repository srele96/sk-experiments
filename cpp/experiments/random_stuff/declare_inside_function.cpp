#include <iostream>

// https://stackoverflow.com/questions/681068/declaring-structures-within-functions-in-c

// https://www.quora.com/In-C-code-whats-the-difference-between-a-variable-and-a-function

// http://www.columbia.edu/itc/sipa/math/variables.html
// A great definition of function vs variable.
//
// Remember that variables are items which can assume different values. A
// function tries to explain one variable in terms of another.

// https://stackoverflow.com/questions/876048/why-can-i-define-structures-and-classes-within-a-function-in-c
int main() {
  struct foo {
    int val{10};
  };

  std::cout << "The foo is: " << foo{}.val << "\n";

  return 0;
}
