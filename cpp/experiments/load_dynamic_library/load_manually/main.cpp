#include <iostream>

#include "windows.h"

int main() {
  HMODULE library = LoadLibrary(TEXT("Library.dll"));

  if (library == nullptr) {
    std::cerr << "Failed to load: Library.dll\n";
  }

  std::cout << "Loaded: Library.dll\n";

  using fptr_library_getint = int (*)();
  fptr_library_getint library_getint = reinterpret_cast<fptr_library_getint>(
      GetProcAddress(library, "library_getint"));

  if (library_getint == nullptr) {
    std::cerr << "Failed to find: library_getint\n";
  } else {
    std::cout << "Call `library_getint`: " << library_getint() << "\n";
  }

  using fptr_library_setint = void (*)(int*);
  fptr_library_setint library_setint = reinterpret_cast<fptr_library_setint>(
      GetProcAddress(library, "library_setint"));

  if (library_setint == nullptr) {
    std::cerr << "Failed to find: library_setint\n";
  } else {
    int result = 0;
    library_setint(&result);
    std::cout << "Call `library_setint`: " << result << "\n";
  }

  FreeLibrary(library);

  return 0;
}
