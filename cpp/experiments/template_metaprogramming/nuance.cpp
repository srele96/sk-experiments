#include <iostream>
#include <string>
#include <utility>

template <typename T>
class a {
 private:
  T t;

 public:
  operator T() const { return t; }
  operator T&() { return t; }

  a& operator=(const T& p_t) {
    std::cout << "copy type T " << p_t << "\n";
    t = p_t;
    return *this;
  }
  a& operator=(T&& p_t) {
    std::cout << "move type T " << p_t << "\n";
    t = std::move(p_t);
    return *this;
  }

  a& operator=(const a& p_a) {
    if (this != &p_a) {
      std::cout << "copy " << p_a << "\n";
      t = p_a.t;
    }
    return *this;
  }
  a& operator=(a&& p_a) {
    std::cout << "move " << p_a << "\n";
    t = std::move(p_a.t);
    return *this;
  }

  // https://en.cppreference.com/w/cpp/language/operators#Comparison_operators
  // Cool! Define others in terms of the previously defined ones.
  friend bool operator<(const a& lhs, const a& rhs) {
    std::cout << lhs << " less than " << rhs << "\n";
    return lhs.t < rhs.t;
  }
  friend bool operator>(const a& lhs, const a& rhs) {
    std::cout << lhs << " more than " << rhs << "\n";
    return rhs < lhs;
  }
  friend bool operator<=(const a& lhs, const a& rhs) {
    std::cout << lhs << " less than or equal " << rhs << "\n";
    return !(lhs > rhs);
  }
  friend bool operator>=(const a& lhs, const a& rhs) {
    std::cout << lhs << " more than or equal " << rhs << "\n";
    return !(lhs < rhs);
  }

  // required due to my usage...
  friend std::ostream& operator<<(std::ostream& ostream, const a& p_a) {
    return ostream << p_a.t;
  }
};

struct b {
  int a = 1, b = 2, c = 3;

  std::string str() const {
    return std::to_string(a) + " " + std::to_string(b) + " " +
           std::to_string(c);
  }

  // gotta define these due to the usage above
  friend bool operator<(const struct b& lhs, const struct b& rhs) {
    std::cout << lhs.str() << " less than " << rhs.str() << "\n";
    return lhs.a < rhs.a && lhs.b < rhs.b && lhs.c < rhs.c;
  }
  friend bool operator>(const struct b& lhs, const struct b& rhs) {
    std::cout << lhs.str() << " more than " << rhs.str() << "\n";
    return rhs < lhs;
  }
  friend bool operator<=(const struct b& lhs, const struct b& rhs) {
    std::cout << lhs.str() << " less than or equal " << rhs.str() << " \n";
    return !(lhs > rhs);
  }
  friend bool operator>=(const struct b& lhs, const struct b& rhs) {
    std::cout << lhs.str() << " more than or equal " << rhs.str() << "\n";
    return !(lhs < rhs);
  }

  // required due to my usage...
  friend std::ostream& operator<<(std::ostream& ostream, const struct b& p_b) {
    return ostream << p_b.str();
  }
};

namespace sk {

class foo_t {
 public:
  template <typename T>
  foo_t& operator<<(T&& p_t) {
    std::cout << std::forward<T>(p_t);
    return *this;
  }
};

foo_t foo;

}  // namespace sk

int main() {
  a<int> a_int1{};
  a<int> a_int2{};
  a_int1 = 1;
  a_int2 = 2;
  std::cout << a_int1 << "\n";

  a<b> a_b1;
  a<b> a_b2;

  std::cout << "----\ntest the object operator overloads\n----\n";

  std::cout << "  - use copy assignment\n";
  a_int1 = a_int2;
  a_int2 = a_int1;
  a_b1 = a_b2;

  std::cout << "  - use move assignment\n";
  a_int1 = 2;
  a_b1 = b{4, 5, 6};

  std::cout << "  - use less than operator\n";
  a_b1 < a_b2;

  std::cout << "  - use more than operator\n";
  a_b1 > a_b2;

  std::cout << "  - use less than or equal operator\n";
  a_b1 <= a_b2;

  std::cout << "  - use more than or equal operator\n";
  a_b1 >= a_b2;

  std::cout << "----\ntest the operator overloads\n----\n";
  sk::foo << "hello world\n";
  sk::foo << a_b1;

  return 0;
}
