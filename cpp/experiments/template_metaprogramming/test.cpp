// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// I was surprised that a whole test suite becomes an executable. That makes
// since this file would compile to an executable.
//
// I have a lot of findings from this journey!
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <algorithm>
#include <iostream>
#include <memory>
#include <utility>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

namespace design_pattern {

// https://en.cppreference.com/w/cpp/memory/enable_shared_from_this
class observer : public std::enable_shared_from_this<observer> {
 public:
  std::shared_ptr<observer> getptr() { return shared_from_this(); }

  [[nodiscard]] static std::shared_ptr<observer> create() {
    return std::shared_ptr<observer>(new observer());
  }

  // Overloaded operator can not be mocked using google test framework
  //  - Use a differently named method to test it
  //    - Differently named method can not be tested, can't overload
  //  - Create an interface
  //    - Can not template a virtual method
  //      - Create a data wrapper to generalize taken data and remove template
  //
  // template<typename T> void operator()(T&& p_data) const

  template <typename T>
  void on_data(T&& data) const {
    std::cout << data << "\n";
  }

 private:
  observer() = default;
};

class subject {
 public:
  void subscribe(const std::weak_ptr<observer>& p_observer) {
    m_observers.push_back(p_observer);
  }

  template <typename T>
  void notify(T&& data) {
    std::for_each(m_observers.begin(), m_observers.end(),
                  [data = std::forward<T>(data)](
                      std::weak_ptr<observer>& p_observer) mutable {
                    auto ptr_observer{p_observer.lock()};
                    if (ptr_observer) {
                      ptr_observer->on_data(data);
                    }
                  });
  }

 private:
  std::vector<std::weak_ptr<observer>> m_observers;
};

}  // namespace design_pattern

namespace data {

struct printer {
  int m_a;
  int m_b;
  int m_c;
};

std::ostream& operator<<(std::ostream& ostream, const printer& p_printer) {
  ostream << "(" << p_printer.m_a << ", " << p_printer.m_b << ", "
          << p_printer.m_c << ")";

  return ostream;
}

}  // namespace data

namespace mock {

// I decided to make a mock implementation, however, I did not program to an
// interface... Awesome!

}

TEST(HelloTest, BasicAssertions) {
  design_pattern::subject subject;

  std::shared_ptr<design_pattern::observer> ptr_observer_a{
      design_pattern::observer::create()};
  std::shared_ptr<design_pattern::observer> ptr_observer_b{
      design_pattern::observer::create()};
  std::shared_ptr<design_pattern::observer> ptr_observer_c{
      design_pattern::observer::create()};

  subject.subscribe(ptr_observer_a);
  subject.subscribe(ptr_observer_b);
  subject.subscribe(ptr_observer_c);

  constexpr int param_a{1};
  constexpr int param_b{2};
  constexpr int param_c{3};

  subject.notify(data::printer{param_a, param_b, param_c});

  // I made a lot of observations and eye-opening discoveries even though I did
  // not finish the test as i wanted to.

  EXPECT_STRNE("hello", "world");
  EXPECT_EQ(7 * 6, 42);
}
