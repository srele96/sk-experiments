#include <iostream>
#include <type_traits>
#include <utility>

namespace one {

template <typename... Rest>
struct __store {
  template <typename U>
  void set(U v) {
    std::cout << "type not found\n";
  }

  template <typename U>
  U get() const {
    std::cout << "type not found\n";
  }
};

template <typename T, typename... Rest>
struct __store<T, Rest...> : public __store<Rest...> {
  T value;

  template <typename U>
  void set(U v) {
    if constexpr (std::is_same_v<T, U>) {
      value = std::move(v);
    } else {
      __store<Rest...>::template set<U>(v);
    }
  }

  template <typename U>
  U get() const {
    if constexpr (std::is_same_v<T, U>) {
      return value;
    } else {
      return __store<Rest...>::template get<U>();
    }
  }
};

}  // namespace one

namespace two {

template <typename T, typename... Rest>
struct __store : public __store<Rest...> {
  T value;

  template <typename U>
  void set(U v) {
    __store<Rest...>::set(v);
  }

  template <typename U>
  U get() const {
    return __store<Rest...>::template get<U>();
  }
};

template <typename T>
struct __store<T> {
  T value;

  template <typename U>
  void set(U v) {
    value = std::move(v);
  }

  template <typename U>
  U get() const {
    return value;
  }
};

}  // namespace two

int main() {
  {  // Explore functionality and values stored in namespace one
    one::__store<int, char, float> store;

    std::cout << "store.value = " << store.value << "\n";

    store.set<int>(1);
    std::cout << store.get<int>() << "\n";

    std::cout << "store.value = " << store.value << "\n";

    store.set<char>('a');
    std::cout << store.get<char>() << "\n";

    std::cout << "store.value = " << store.value << "\n";

    store.set<float>(1.5);
    std::cout << store.get<float>() << "\n";

    std::cout << "store.value = " << store.value << "\n";

    store.set<char>('b');
    std::cout << store.get<char>() << "\n";

    std::cout << "store.value = " << store.value << "\n";

    store.set<double>(1.5);
    std::cout << store.get<double>() << "\n";
  }

  std::cout << "\n------------------------\n\n";

  {  // Explore functionality and values stored in namespace two
    two::__store<int, char, float> store;

    std::cout << "store.value = " << store.value << "\n";

    store.set<int>(1);
    std::cout << store.get<int>() << "\n";

    std::cout << "store.value = " << store.value << "\n";

    store.set<char>('a');
    std::cout << store.get<char>() << "\n";

    std::cout << "store.value = " << store.value << "\n";

    store.set<float>(1.5);
    std::cout << store.get<float>() << "\n";

    std::cout << "store.value = " << store.value << "\n";

    store.set<char>('b');
    std::cout << store.get<char>() << "\n";

    std::cout << "store.value = " << store.value << "\n";
  }

  {  // Test out the empty variadic arguments

    one::__store<> store;
  }

  return 0;
}
