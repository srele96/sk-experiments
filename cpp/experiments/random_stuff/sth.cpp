#include <functional>
#include <iostream>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>

template <typename T>
struct something {
  T operator()(const T& t) {
    std::cout << "something\n";
    return t;
  }
};

template <typename Ret, typename... Args>
struct something<Ret(Args...)> {
  using function_type = Ret(Args...);

  Ret operator()(const std::function<void(Args...)>& fun, Args... args) {
    std::cout << "function type\n";

    fun(args...);

    return Ret();
  }
};

// Why would I instantiate a type inside a template parameter?
template <typename _Tp, _Tp __v>
struct foo {
  static constexpr _Tp value = __v;
  typedef _Tp value_type;
  // What is integral constant?
  // What is this type of overload, it is the first time I see it.
  constexpr operator value_type() const noexcept { return value; }
};

// // NO CLUE --------------------------------------------

// template <typename T, typename... List>
// struct contains;

// template <typename T, typename... List>
// struct contains<T, T, List...> : std::true_type {};

// template <typename T, typename U, typename... List>
// struct contains<T, U, List...> : contains<T, List...> {};

// template <typename T>
// struct contains<T> : std::false_type {};

// // NO CLUE --------------------------------------------

// struct cont_base {};

// template <typename T, typename... Rest>
// struct cont : public cont<Rest...> {
//  private:
//   T value;

//  public:
//   void set(T v) { value = std::move(v); }
//   T get() const { return value; }

//   // NO CLUE --------------------------------------------

//   // template <typename U>
//   // void set(U v) {
//   //   cont<Rest...>::set(v);
//   // }

//   // template <typename U>
//   // U get() const {
//   //   return cont<Rest...>::template get<U>();
//   // }

//   template <typename U>
//   std::enable_if_t<std::is_same_v<T, U>, U> get() const {
//     return value;
//   }

//   template <typename U>
//   std::enable_if_t<!std::is_same_v<T, U>, U> get() const {
//     return cont<Rest...>::template get<U>();
//   }

//   template <typename U>
//   std::enable_if_t<std::is_same_v<T, U>> set(U v) {
//     value = std::move(v);
//   }

//   template <typename U>
//   std::enable_if_t<!std::is_same_v<T, U>> set(U v) {
//     cont<Rest...>::template set<U>(v);
//   }

//   // NO CLUE --------------------------------------------
// };

// template <typename T>
// struct cont<T> : public cont_base {
//  private:
//   T value;

//  public:
//   void set(T t) { value = std::move(t); }
//   T get() const { return value; }
// };

// template <>
// struct cont<void> : public cont_base {
//   //
// };

///////////////////////////////////////////////////////////////////////////////

template <typename... Ts>
using are_unique = std::conjunction<
    std::is_same<Ts, typename std::remove_reference<Ts>::type>...>;

template <typename... Ts>
constexpr bool are_unique_v = are_unique<Ts...>::value;

// Store class
template <typename... Ts>
class Store {
  static_assert(are_unique_v<Ts...>, "All types in Store must be unique");

  std::tuple<Ts...> data;

 public:
  // Get value by type
  template <typename T>
  T get() const {
    return std::get<T>(data);
  }

  // Set value by type
  template <typename T>
  void set(const T& value) {
    std::get<T>(data) = value;
  }
};

///////////////////////////////////////////////////////////////////////////////

template <typename T>
struct _store_item {
  T value;
};

template <typename... Args>
struct _store : public _store_item<Args>... {
  template <typename T>
  T get() const {
    return _store_item<T>::value;
  }

  template <typename T>
  void set(const T& value) {
    _store_item<T>::value = value;
  }
};

///////////////////////////////////////////////////////////////////////////////

int main() {
  something<int(int, const std::string&)> sth;

  sth(
      [](int i, const std::string& hello) {
        std::cout << "fun: " << i << ", " << hello << "\n";
      },
      1, "hello");

  something<int> sth2;
  sth2(1);

  foo<int, 1> f;

  std::cout << f.value << ", " << f << "\n";

  struct bar {};

  // foo<bar, bar{}> f2;
  //
  // std::cout << f2.value << ", " << f2 << "\n";

  // cont<char, int, float> c;

  // c.set<int>(1);
  // std::cout << c.get<int>() << "\n";
  // c.set<int>(5);
  // std::cout << c.get<int>() << "\n";

  // c.set<float>(6.6f);
  // std::cout << c.get<float>() << "\n";

  // c.set<char>('a');
  // std::cout << c.get<char>() << "\n";

  Store<int, float, char> s;
  s.set<int>(1);
  std::cout << s.get<int>() << "\n";
  s.set<float>(6.6f);
  std::cout << s.get<float>() << "\n";
  s.set<char>('a');
  std::cout << s.get<char>() << "\n";

  _store<int, float, char> s2;
  s2.set<int>(55);
  std::cout << s2.get<int>() << "\n";
  s2.set<float>(9.8f);
  std::cout << s2.get<float>() << "\n";
  s2.set<char>('h');
  std::cout << s2.get<char>() << "\n";

  return 0;
}
