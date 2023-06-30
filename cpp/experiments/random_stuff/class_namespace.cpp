#include <iostream>
#include <typeinfo>

namespace foo {

class bar {
 private:
  int m_val;

 public:
  int val() const { return m_val; }
  void val(int val) { m_val = val; }

  class baz {
   private:
    int m_val;

   public:
    int val() const { return m_val; }
    void val(int val) { m_val = val; }
  };
};

class baz {
 private:
  int m_val;

 public:
  int val() && {
    std::cout << typeid(*this).name() << " rvalue\n";
    return m_val;
  }
  int val() & {
    std::cout << typeid(*this).name() << " lvalue\n";
    return m_val;
  }
  void val(int val) && {
    std::cout << typeid(*this).name() << " rvalue set " << val << "\n";
    m_val = val;
  }
  void val(int val) & {
    std::cout << typeid(*this).name() << " lvalue set " << val << "\n";
    m_val = val;
  }
};

}  // namespace foo

int main() {
  foo::bar bar;
  bar.val(1);
  foo::bar::baz baz;
  baz.val(2);

  std::cout << "bar.val() = " << bar.val() << "\n"
            << "baz.val() = " << baz.val() << "\n";

  foo::baz().val(3);
  foo::baz().val();
  foo::baz lval_baz;
  lval_baz.val(4);
  lval_baz.val();

  return 0;
}
