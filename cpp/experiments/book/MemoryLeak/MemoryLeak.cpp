#include "MemoryLeak.h"

#include <iostream>

using namespace std;

MemoryLeak::MemoryLeak() { cout << "Create - MemoryLeak." << endl; }

MemoryLeak::~MemoryLeak() { cout << "Delete - MemoryLeak." << endl; }
