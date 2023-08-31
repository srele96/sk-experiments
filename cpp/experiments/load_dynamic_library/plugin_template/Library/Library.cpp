#include "Library.h"

#include <fstream>
#include <iostream>
#include <string>

LibraryPlugin::~LibraryPlugin() {}

LibraryInterface::~LibraryInterface() {}

void Library::RegisterPlugin(const char* key, const LibraryPlugin* plugin) {
  m_plugin[key] = plugin;
}

void Library::UnregisterPlugin(const char* key) { m_plugin.erase(key); }

const char* Library::Test() { return "Test"; }

void Library::Evaluate(const char* filePath, Callback callback) {
  std::ifstream file{filePath};
  std::string word;

  while (file >> word) {
    callback(word.c_str());
  }
}

Library::~Library() {}

extern "C" {
LibraryInterface* CreateLibrary() { return new Library; }

void DeleteLibrary(LibraryInterface* library) {
  delete library;  // NOLINT
}
}
