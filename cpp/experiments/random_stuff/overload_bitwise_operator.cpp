#include <iostream>
#include <string>

namespace overload_bitwise_operator {
class foo {
 public:
  std::string m_s;
  // ... It is simply a bitwise operator... it isn't anything special... I
  // always thought it's something special. I guess they must have overloaded
  // bitwise operator because it resembles that we insert something into an
  // object because of "<<" characters that point to an object.
  foo& operator<<(std::string const& str) {
    m_s = str;

    return *this;
  }
};
}  // namespace overload_bitwise_operator

int main() {
  overload_bitwise_operator::foo foo;
  std::cout << "Before: " << foo.m_s << "\n";
  foo << "wtf";
  std::cout << "After: " << foo.m_s << "\n";
  return 0;
}
