#include "Library.h"

extern "C" int library_getint() { return 5; }

extern "C" void library_setint(int* ptr) { *ptr = 10; }
