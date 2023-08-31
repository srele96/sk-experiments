#include "Library.h"

LibraryInterface::~LibraryInterface() {}

const char* Library::Test() { return "Test"; }
Library::~Library() {}

extern "C" {
LibraryInterface* CreateLibrary() { return new Library; }

void DeleteLibrary(LibraryInterface* library) {
  delete library;  // NOLINT
}
}
