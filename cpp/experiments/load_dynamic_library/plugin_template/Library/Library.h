#ifndef LOAD_DYNAMIC_LIBRARY_ASD_LIBRARY_H
#define LOAD_DYNAMIC_LIBRARY_ASD_LIBRARY_H

#include <string>
#include <unordered_map>

class LibraryPlugin {
 public:
  LibraryPlugin() = default;
  LibraryPlugin(const LibraryPlugin&) = delete;
  LibraryPlugin& operator=(const LibraryPlugin&) = delete;
  LibraryPlugin(LibraryPlugin&&) = delete;
  LibraryPlugin& operator=(LibraryPlugin&&) = delete;
  virtual ~LibraryPlugin() = 0;

  virtual const char* OnWord(const char* word) = 0;
};

extern "C" {
class LibraryInterface {
 public:
  LibraryInterface() = default;
  LibraryInterface(const LibraryInterface&) = delete;
  LibraryInterface& operator=(const LibraryInterface&) = delete;
  LibraryInterface(LibraryInterface&&) = delete;
  LibraryInterface& operator=(LibraryInterface&&) = delete;
  virtual ~LibraryInterface() = 0;

  virtual void RegisterPlugin(const char* key, const LibraryPlugin* plugin) = 0;
  virtual void UnregisterPlugin(const char* key) = 0;

  virtual const char* Test() = 0;

  using Callback = void (*)(const char*);
  virtual void Evaluate(const char* filePath, Callback callback) = 0;
};
}

class Library : public LibraryInterface {
 private:
  std::unordered_map<std::string, const LibraryPlugin*> m_plugin;

 public:
  Library() = default;
  Library(const Library&) = delete;
  Library& operator=(const Library&) = delete;
  Library(Library&&) = delete;
  Library& operator=(Library&&) = delete;
  ~Library() override;

  auto RegisterPlugin(const char* key, const LibraryPlugin* plugin)
      -> void override;
  auto UnregisterPlugin(const char* key) -> void override;

  auto Test() -> const char* override;

  auto Evaluate(const char* filePath, Callback callback) -> void override;
};

#endif
