#ifndef LOAD_DYNAMIC_LIBRARY_WITH_CPP_LINKAGE_LIBRARY_H
#define LOAD_DYNAMIC_LIBRARY_WITH_CPP_LINKAGE_LIBRARY_H

#include <string>

__declspec(dllexport) int library_add(int, int);

namespace Library {

__declspec(dllexport) int Add(int, int);

class __declspec(dllexport) X {
 private:
  std::string m_str;

 public:
  explicit X(std::string str);
  std::string str() const;
  void str(std::string str);
};

}  // namespace Library

#endif
