#include <windows.h>

#include <iostream>

#include "Library/Library.h"

int main() {
  HMODULE Library{LoadLibrary(TEXT("Library.dll"))};

  if (Library == nullptr) {
    std::cerr << "Failed to load:: Library.dll";
  }

  using FptrCreateLibrary = LibraryInterface* (*)();
  using FptrDeleteLibrary = void (*)(LibraryInterface*);

  FptrCreateLibrary CreateLibrary{
      reinterpret_cast<FptrCreateLibrary>(  // NOLINT
          GetProcAddress(Library, "CreateLibrary"))};
  if (CreateLibrary == nullptr) {
    std::cerr << "Failed to find: CreateLibrary\n";
  }

  FptrDeleteLibrary DeleteLibrary{
      reinterpret_cast<FptrDeleteLibrary>(  // NOLINT
          GetProcAddress(Library, "DeleteLibrary"))};
  if (DeleteLibrary == nullptr) {
    std::cerr << "Failed to find: DeleteLibrary\n";
  }

  LibraryInterface* LibraryInstance{CreateLibrary()};

  std::cout << LibraryInstance->Test() << "\n";

  // Works... How do I want to use the plugin? Just imagine that the calls to
  // functions do what I want them to.

  DeleteLibrary(LibraryInstance);
  FreeLibrary(Library);

  return 0;
}
