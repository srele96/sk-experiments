#include <iostream>

#include "MemoryLeak.h"

using namespace std;

// Specs:
// Cause a memory leak from function scope.
// Use dynamic allocation using operator new.
// ----
// 1.
// Create a constructor and destructor that prints the class name.
// ----
// 2.
// On the contrary, create oposing case.
// Use dynamic allocation but clean it before exiting the function scope.
// ----
// 3.
// Lastly, use smart pointers to dynamically allocate same class.
// ----
// 4.
// Observe the output and note the results.
//
// Print the function name at start and end of it's body.

void use_new_dont_delete() {
  cout << "use_new_dont_delete - start" << endl;
  auto do_i_leak_out_of_scope = new MemoryLeak();
  cout << "use_new_dont_delete - end" << endl;
}

void dont_use_new_dont_delete() {
  cout << "dont_use_new_dont_delete - start" << endl;
  MemoryLeak leak;
  cout << "dont_use_new_dont_delete - end" << endl;
}

void use_new_and_delete() {
  cout << "use_new_and_delete - start" << endl;
  auto leak = new MemoryLeak();
  delete leak;
  cout << "use_new_and_delete - end" << endl;
}

int main() {
  use_new_dont_delete();
  dont_use_new_dont_delete();
  use_new_and_delete();
  return 0;
}
