#include <iostream>
#include <string>

namespace curiously_recurring_template_pattern {

namespace a {

template <class T>
class base {
 public:
  void interface() { static_cast<T*>(this)->implementation(); }

  void implementation() { std::cout << "Base implementation.\n"; }
};

class derived : public base<derived> {
 private:
  const int m_initial_x{5};
  int m_x{m_initial_x};

 public:
  void implementation() const {
    std::cout << "Derived implementation: " << m_x << "\n";
  }
};

}  // namespace a

namespace b {

class base {
 public:
  void interface() { implementation(); }
  void implementation() { std::cout << "Base implementation\n"; }
};

class derived : public base {
 public:
  void implementation() { std::cout << "Derived implementation\n"; }
};

}  // namespace b

// Does it work if the derived override the interface method?
namespace c {

template <class T>
class base {
 public:
  void interface() { static_cast<T*>(this)->implementation(); }

  void implementation() { std::cout << "Base implementation.\n"; }
};

class derived : public base<derived> {
 private:
  const int m_initial_x{5};
  int m_x{m_initial_x};

 public:
  void implementation() const {
    std::cout << "Derived implementation: " << m_x << "\n";
  }

  void interface() { std::cout << "Derived interface\n"; }
};

}  // namespace c

}  // namespace curiously_recurring_template_pattern

int main() {
  const std::string SEPARATOR{"\n--------\n\n"};

  curiously_recurring_template_pattern::a::derived derived_a;
  // Both call derived implementation.
  derived_a
      .interface();  // Derived class calls an interface method of the base
                     // class which is compile time polymorphism. Which calls
                     // the interface from base class which casts (this) to the
                     // templated parameter to call the member method.
  derived_a.implementation();

  std::cout << SEPARATOR;

  curiously_recurring_template_pattern::b::derived derived_b;
  derived_b.interface();
  derived_b.implementation();

  std::cout << SEPARATOR;

  curiously_recurring_template_pattern::c::derived derived_c;
  derived_c.interface();
  derived_c.implementation();

  return 0;
}
