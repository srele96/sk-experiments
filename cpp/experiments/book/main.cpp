#include <iostream>
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
int main() {
  cout << "Print something for the sake of it.";
  return 0;
}
