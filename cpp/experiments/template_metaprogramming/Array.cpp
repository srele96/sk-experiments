#include <array>
#include <cstddef>
#include <iostream>

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Note!
//
// An exploration of how to fill up the array using template metaprogramming
// because I wanted to write an algorithm to generate prime numbers at compile
// time. The main issue is assignment operation is mutable operation while
// template metaprogramming is pure functional programming.
//
// Hence this piece explores possible ways to fill up an array in template
// metaprogramming which I could use to fill up an array of prime numbers at
// compile time.
//
// Divide and Conquer.
//
// By first learning how to fill up an array, I offloaded that task's knowledge
// to long term memory and can use it to solve the original problem, now that I
// know how to fill up an array.
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Nope...

// template<size_t n, size_t i = 0, bool = (i >= n)>
// struct a_helper {
//   // a_helper<n, i + 1>;
// };

// template<size_t n, size_t i>
// struct a_helper<n, i, true> {

// };

// template<size_t n, size_t i = 0>
// struct a : a_helper<n, i> {
//   std::array<size_t, n>
// };

// fn(n, i = 0) {
//   if (i < n) {
//     fn(n, i + 1);
//     list[i] = i;
//   }
//   return list;
// }

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Nope, won't work

// template <std::size_t n, std::size_t... I>
// struct GenerateArray {
//   using type = typename GenerateArray<n - 1, n - 1, I...>::type;
// };

// template <std::size_t... I>
// struct GenerateArray<0, I...> {
//   static constexpr std::array<size_t, sizeof...(I)> value{{I...}};
// };

// template<std::size_t n>
// struct a {
//   static constexpr auto value = GenerateArray<n>::value;
// };

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// Nope, this neither

// template <std::size_t n, std::size_t... I>
// struct ArrayGenerator {
//   using type = typename ArrayGenerator<n - 1, n - 1, I...>::type;
// };

// template <std::size_t... I>
// struct ArrayGenerator<0, I...> {
//   static constexpr std::array<std::size_t, sizeof...(I)> value = {{I...}};
// };

// template <std::size_t n>
// struct Gen {
//   static constexpr auto value = ArrayGenerator<n>::value;
// };

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// the idea
//
// provide variadic template arguments explicit thing and fill up a std::array
// with it
//
//  -at compile time make sure the user provided amount of variadic elements
//  fits the std array
//
// - and at compile time calculate the amount of variadic elements and create
// std:;array of that length and assign them all to the std::array

namespace Size {

namespace Implicit {

template <int... Values>
struct Array {
  // Check if we assert the amount of values of size of one value
  // static_assert(sizeof...(Values) == 0, "Is not the amount of values");
  // Is it possible to assert how many values are created?
  // Does it even make sense to evaluate?

  constexpr static std::array<int, sizeof...(Values)> value = {{Values...}};
};

}  // namespace Implicit

namespace Explicit {

template <std::size_t N, int... Values>
struct Array {
  static_assert(sizeof...(Values) == N,
                "Not enough values to instantiate std::array!");

  constexpr static std::array<int, N> value = {{Values...}};
};

}  // namespace Explicit

}  // namespace Size

int main() {
  {
    constexpr auto array{Size::Implicit::Array<>::value};

    std::cout << "(Size::Implicit::Array) Values are:\n";

    for (const auto& value : array) {
      std::cout << value << " ";
    }

    std::cout << "\n";
  }

  {
    constexpr auto array{Size::Implicit::Array<1>::value};

    std::cout << "(Size::Implicit::Array) Values are:\n";

    for (const auto& value : array) {
      std::cout << value << " ";
    }

    std::cout << "\n";
  }

  {
    constexpr auto array{Size::Implicit::Array<1, 2, 3, 4>::value};

    std::cout << "(Size::Implicit::Array) Values are:\n";

    for (const auto& value : array) {
      std::cout << value << " ";
    }

    std::cout << "\n";
  }

  {
    // constexpr auto array{Size::Explicit::Array<5>::value};
    // Can i catch static assert failures?
    //
    // I wanted some kind of logging or runtime message how compile time
    // evaluation has failed, if that makes sense at all.
    //
    // Nope. Can't catch it at compile or runtime.

    constexpr auto array{Size::Explicit::Array<5, 4, 4, 4, 4, 4>::value};

    std::cout << "(Size::Explicit::Array) Values are:\n";

    for (const auto& value : array) {
      std::cout << value << " ";
    }

    std::cout << "\n";
  }

  return 0;
}
