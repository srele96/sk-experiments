#include <iostream>

int main() {
  const size_t gigabyte = 4294967296;
  // allocate 4gb of memory
  int *p = new int[gigabyte];
  for (size_t i = 0; i < gigabyte; i++) {
    p[i] = 1;
  }
  // pause the program by waiting for user input
  std::cin.get();

  // free the memory
  delete[] p;

  return 0;
}
