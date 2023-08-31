#ifndef LOAD_DYNAMIC_LIBRARY_ASD_LIBRARY_H
#define LOAD_DYNAMIC_LIBRARY_ASD_LIBRARY_H

extern "C" {
class LibraryInterface {
 public:
  LibraryInterface() = default;
  LibraryInterface(const LibraryInterface&) = delete;
  LibraryInterface& operator=(const LibraryInterface&) = delete;
  LibraryInterface(LibraryInterface&&) = delete;
  LibraryInterface& operator=(LibraryInterface&&) = delete;
  virtual ~LibraryInterface() = 0;

  virtual const char* Test() = 0;
};
}

class Library : public LibraryInterface {
 public:
  Library() = default;
  Library(const Library&) = delete;
  Library& operator=(const Library&) = delete;
  Library(Library&&) = delete;
  Library& operator=(Library&&) = delete;
  ~Library() override;

  auto Test() -> const char* override;
};

#endif
