#include <iostream>
#include <memory>

#include "MemoryLeak.h"

using namespace std;

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

void use_smart_pointer() {
  cout << "use_smart_pointer - start" << endl;
  unique_ptr<MemoryLeak>(new MemoryLeak());
  cout << "use_smart_pointer - start" << endl;
}

int main() {
  use_new_dont_delete();
  dont_use_new_dont_delete();
  use_new_and_delete();
  use_smart_pointer();
  return 0;
}