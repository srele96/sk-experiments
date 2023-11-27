#ifndef LOAD_DYNAMIC_LIBRARY_LOAD_USING_LOADER_LOADER_LIBRARY
#define LOAD_DYNAMIC_LIBRARY_LOAD_USING_LOADER_LOADER_LIBRARY

#include <iostream>

#include "windows.h"

#ifdef USE_CLASS

class Library {
 private:
  using fptr_library_getint = int (*)();
  using fptr_library_setint = void (*)(int*);

  HMODULE dll;

  fptr_library_getint library_getint;
  fptr_library_setint library_setint;

 public:
  Library()
      : dll{LoadLibrary(TEXT("Library.dll"))},
        library_getint{reinterpret_cast<fptr_library_getint>(
            GetProcAddress(dll, "library_getint"))},
        library_setint{reinterpret_cast<fptr_library_setint>(
            GetProcAddress(dll, "library_setint"))} {
    if (dll == nullptr) {
      throw std::runtime_error("Failed to load Library.dll!");
    }
    if (library_getint == nullptr) {
      throw std::runtime_error("Failed to find: library_getint!");
    }
    if (library_setint == nullptr) {
      throw std::runtime_error("Failed to find: library_setint!");
    }
  }
  Library(const Library&) = delete;
  Library& operator=(const Library&) = delete;
  Library(Library&&) = delete;
  Library& operator=(Library&&) = delete;
  ~Library() { FreeLibrary(dll); }

  void setint(int* ptr) { library_setint(ptr); }

  int getint() { return library_getint(); }
};

#else

// I dislike the fact that the user can access function pointers types,
// instantiated function pointers and handle to the library. I am aware of my
// own limitations in that aspect, hence, for learning purposes, i deem it ok...

using fptr_library_getint = int (*)();
using fptr_library_setint = void (*)(int*);

// It is disastrous that the user can redefine these and ruin the whole
// library... lol I find it hilarious! I don't know a better technique and fuck
// it for now, I achieved what I wanted!

fptr_library_getint library_getint = nullptr;
fptr_library_setint library_setint = nullptr;

HMODULE library = nullptr;

void library_init() {
  library = LoadLibrary(TEXT("Library.dll"));

  if (library == nullptr) {
    std::cerr << "Failed to load: Library.dll\n";
  }

  library_getint = reinterpret_cast<fptr_library_getint>(
      GetProcAddress(library, "library_getint"));
  if (library_getint == nullptr) {
    std::cerr << "Failed to find: library_getint!\n";
  }

  library_setint = reinterpret_cast<fptr_library_setint>(
      GetProcAddress(library, "library_setint"));
  if (library_setint == nullptr) {
    std::cerr << "Failed to find: library_setint!\n";
  }
}

void library_free() { FreeLibrary(library); }

#endif  // USE_CLASS

#endif  // LOAD_DYNAMIC_LIBRARY_LOAD_USING_LOADER_LOADER_LIBRARY
