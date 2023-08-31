#include <libloaderapi.h>

#include <functional>
#include <iostream>
#include <string>

#include "Library/Library.h"

class AppendPlugin : public LibraryPlugin {
  AppendPlugin() = default;
  ~AppendPlugin() override {}

  auto OnWord(const char* word) -> const char* override {
    std::string result{std::string{word} + " -- "};
    // TODO: Fix return address to deleted memory.
    // I can't join two sequences of characters without dynamic allocation...
    return result.c_str();
  }
};

int main() {
  HMODULE Library{LoadLibrary(TEXT("Library.dll"))};

  if (Library == nullptr) {
    std::cerr << "Failed to load:: Library.dll";
  }

  using FptrCreateLibrary = LibraryInterface* (*)();
  using FptrDeleteLibrary = void (*)(LibraryInterface*);

  const FptrCreateLibrary CreateLibrary{
      reinterpret_cast<FptrCreateLibrary>(  // NOLINT
          GetProcAddress(Library, "CreateLibrary"))};
  if (CreateLibrary == nullptr) {
    std::cerr << "Failed to find: CreateLibrary\n";
  }

  const FptrDeleteLibrary DeleteLibrary{
      reinterpret_cast<FptrDeleteLibrary>(  // NOLINT
          GetProcAddress(Library, "DeleteLibrary"))};
  if (DeleteLibrary == nullptr) {
    std::cerr << "Failed to find: DeleteLibrary\n";
  }

  LibraryInterface* LibraryInstance{CreateLibrary()};

  std::cout << LibraryInstance->Test() << "\n";

  // Works... How do I want to use the plugin? Just imagine that the calls to
  // functions do what I want them to.

  const std::string appendPluginKey{"AppendPlugin"};
  const AppendPlugin* appendPlugin{
      new AppendPlugin{}};  // TODO: Fix linter warning

  // TODO: Fix plugin owner to deallocate memory.
  LibraryInstance->RegisterPlugin(appendPluginKey.c_str(), appendPlugin);

  LibraryInstance->Evaluate(
      "README.md", [](const char* word) { std::cout << word << "\n"; });

  LibraryInstance->UnregisterPlugin(appendPluginKey.c_str());
  delete appendPlugin;
  DeleteLibrary(LibraryInstance);
  FreeLibrary(Library);

  return 0;
}
