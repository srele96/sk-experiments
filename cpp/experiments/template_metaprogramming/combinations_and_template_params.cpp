#include <functional>
#include <iostream>
#include <type_traits>
#include <vector>

template <template <typename> class T,
          template <template <typename> class> class G>
struct f {
  T<int> y;
  T<float> z;
  G<T> w;
};

template <typename T>
struct g {
  T u;
};

template <template <class> class T>
struct h {
  T<int> v;
};

// Also works.
//
// template <template <typename> class T>
// struct h {
//   T<int> v;
// };

// ----------------------------------------------------------------------------
// Try to see how does specialization work

template <int n>
struct spec {
  int x = n;
};

template <>
struct spec<0> {
  int x = 3;
};

// ----------------------------------------------------------------------------

template <int n>
struct rec {
  static constexpr int value{rec<n - 1>::value + 1};
};

template <>
struct rec<0> {
  static constexpr int value{0};
};

// ----------------------------------------------------------------------------

template <typename T>
struct a {
  T o;
};

template <typename T>
struct b {
  struct hey {
    T u;
  };

  hey hey_;
};

// How would i specialize nest

template <template <typename> class T>
struct nest {
  T<int> g;
};

template <typename T>
struct nest_base {
  T x;
};

template <>
struct nest<nest_base> {
  nest_base<int> y;
};

// How would i specialize int n

template <int n>
struct nest2 {
  int x = n;
};

template <>
struct nest2<0> {
  int x = 0;
};

// ----------------------------------------------------------------------------

template <typename G, template <typename> class T,
          template <template <typename> class> class E,
          template <template <template <typename> class> class> class H>
struct nt {
  G g;
  T<G> t;
  E<T> e;
  H<E> h;
};

template <typename T>
struct T_ {
  T t;
};

template <template <typename> class E>
struct E_ {
  E<int> e;
};

template <template <template <typename> class> class H>
struct H_ {
  H<T_> h;
};

template <template <template <template <typename> class> class> class G>
struct G_ {
  G<E_> g;
};

// ----------------------------------------------------------------------------

// This is runtime algorithm to generate combinations of N out of values.
std::vector<std::vector<int>> combinations(int n,
                                           const std::vector<int>& values) {
  std::vector<int> combination;
  std::vector<std::vector<int>> combinations;

  std::function<void(int)> backtrack{
      [&combination, &combinations, n, &values, &backtrack](int start) {
        if (combination.size() == n) {
          combinations.push_back(combination);
          return;
        }

        for (int i = start; i < values.size(); ++i) {
          combination.push_back(values[i]);
          backtrack(i + 1);
          combination.pop_back();
        }
      }};

  backtrack(0);

  return combinations;
}

// Write a template metaprogram that generates combinations at compile-time.
//
// Using variadic templates i can store the current amount of values
// I can expand it to store them in a vector
//
// The issue is how do i know at compile time how many combinations there will
// be for a given N?
//
// There should be a mathematical formula for that, right? Are there other ways
// to calculate how many combinations of N are?

template <std::size_t n>
struct factorial {
  constexpr static std::size_t value{factorial<n - 1>::value * n};
};

template <>
struct factorial<1> {
  constexpr static std::size_t value{1};
};

// should backtracking occur on each level?

template <typename type, std::size_t r, std::size_t n,
          // Calculate the total amount of combinations using mathematical
          // formula based on desired size of each combination and values:
          //
          // n! / r!(n-r)!
          std::size_t len = factorial<n>::value /
                            (factorial<r>::value * factorial<n - r>::value)>
constexpr auto combinations(const std::array<type, n>& array)
    -> std::array<std::array<type, r>, len> {
  constexpr std::array<std::array<type, r>, len> combinations{};

  // the problem as always, with functional programing, we don't have a way to
  // push and pop
  //
  // therefore i'd need an alternative
  //
  // if we have collected all the values, store them to the current combination,
  // exit
  //
  // for each index, take value from that index, start from next one, backtrack
  //
  // try to use function template specialization?
  //
  // that way we recursively at compile time store the index of the start, index
  // of the resulting array where we add, etc...
  //
  // the fucking non pure way of programming really got me fucked up
  //
  //

  return combinations;
}

int main() {
  f<g, h> x;

  x.y = g<int>{};
  x = f<g, h>{};

  x.w.v.u = 0;
  x.w = h<g>{};

  static_assert(spec<0>{}.x == 3, "spec<0>{}.x != 3");
  static_assert(spec<1>{}.x == 1, "spec<1>{}.x != 1");
  static_assert(rec<1>::value == 1, "rec<1>::value != 1");
  static_assert(rec<2>::value == 2, "rec<2>::value != 2");
  static_assert(rec<4>::value == 4, "rec<4>::value != 4");
  static_assert(nest<a>{}.g.o == 0, "nest<a>{}.n.g.o != 0");
  static_assert(nest<nest_base>{}.y.x == 0, "nest<nest_base>{}.n.y.x != 0");
  static_assert(nest<b>{}.g.hey_.u == 0, "nest<b>{}.n.g.hey_.u != 0");

  constexpr nt<int, T_, E_, H_> nt_{};

  static_assert(nt_.g == 0, "nt_.g != 0");
  static_assert(nt_.t.t == 0, "nt_.t.g != 0");
  static_assert(nt_.e.e.t == 0, "nt_.e.e.t != 0");
  static_assert(nt_.h.h.e.t == 0, "nt_.h.h.e.t != 0");

  // Figure out what's wrong. Which type is nt_.h?
  std::cout << typeid(nt_.h.h.e.t).name();

  std::cout << "\nCombinations:\n";
  for (const auto& permutation : combinations(3, {1, 2, 3, 4})) {
    for (const auto& value : permutation) {
      std::cout << value << " ";
    }
    std::cout << "\n";
  }

  // Challenge!
  //
  // Now... Time to write a template metaprogramming algorithm that generates
  // combinations at compile-time.

  static_assert(factorial<3>::value == 6, "3! is not 6");  // Compile time works

  constexpr std::size_t num{5};
  std::cout << "factorial<" << num << ">::value = " << factorial<num>::value
            << "\n";

  {
    for (const auto& combination : combinations<int, 3, 4>({1, 2, 3, 4})) {
      for (const auto& value : combination) {
        std::cout << value << " ";
      }
      std::cout << "\n";
    }
  }

  return 0;
}
