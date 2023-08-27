#include "Loader/Library.h"

int main() {
#ifdef USE_CLASS
  Library library;

  std::cout << "Using class API!\n";
  std::cout << "Call Library::getint: " << library.getint() << "\n";
  int result = 0;
  library.setint(&result);
  std::cout << "Call Library::setint: " << result << "\n";
#else
  library_init();

  std::cout << "Using function API!\n";
  std::cout << "Call library_getint: " << library_getint() << "\n";
  int result = 0;
  library_setint(&result);
  std::cout << "Call library_setint: " << result << "\n";

  library_free();
#endif

  return 0;
}
