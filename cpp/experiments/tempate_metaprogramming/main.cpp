#include <algorithm>
#include <array>
#include <iostream>
#include <type_traits>

constexpr int sum(const int n) {
  int sum{0};

  for (int i{0}; i < n; ++i) {
    sum += i;
  }

  return sum;
}

// Since c++17 allows loops in constrexpr functions
// Complete this example and the recursive template after

template <typename Type>
constexpr Type default_filler(const std::size_t index) {
  return Type{};
}

// 1. Find a way to use default filler
// 2. Find a way for filer to be optional type as well
template <typename Type, std::size_t Length,
          typename Filler = decltype(default_filler<Type>)>
constexpr auto construct(const Filler& fill = default_filler)
    -> std::array<Type, Length> {
  std::array<Type, Length> result{};

  for (std::size_t i{0}; i < Length; ++i) {
    result[i] = fill(i);
  }

  return result;
}

template <typename Type, std::size_t Length>
struct sequence {
  std::array<Type, Length> values{construct<Type, Length>()};
};

template <typename Type, std::size_t Length>
constexpr bool all_expected(const std::array<Type, Length>& array) {
  for (const Type& val : array) {
    // std::cout << val << " "; // Error, not constexpr any more!
    if (val != Type{}) {
      return false;
    }
  }

  return true;
}

struct compile_constructible {
  // Two constants within a struct make assignment problems.
  // const int one = 5;
  // const int two = 10;
  int m_one = 5;
  int m_two = 10;

  // Overload required because of comparison function
  constexpr bool operator!=(const compile_constructible& other) const {
    return m_one != other.m_one && m_two != other.m_two;
  }

  // constexpr compile_constructible() : m_one{5}, m_two{10} {}

  // does it require copy to be compile time invocable?
  // does it require comparison to be compile time invocable?

  // constexpr compile_constructible& operator=(
  //     const compile_constructible& other) = default;

  // constexpr compile_constructible& operator=(
  //     const compile_constructible& other) {
  //   if (this != &other) {
  //     m_one = other.m_one;
  //     m_two = other.m_two;
  //   }

  //   return *this;
  // }
};

int main() {
  {
    constexpr int end{10};
    constexpr int result = sum(end);

    static_assert(
        // Expected value at compile time.
        result == 45,
        // Message if value is not correct at compile time
        "Failed to compute result at compile time");

    std::cout << result << "\n";
  }

  {
    constexpr size_t length{20};
    constexpr sequence<int, length> seq;

    static_assert(seq.values.size() == length,
                  "Sequence's size is different than required length!");

    static_assert(all_expected(seq.values),
                  "Unexpected value within seq.values!");
  }

  {
    constexpr std::size_t length{20};
    constexpr sequence<compile_constructible, length> seq;

    static_assert(seq.values.size() == length,
                  "Compile-Constructed seq.values");

    static_assert(all_expected(seq.values),
                  "Unexpected value within seq.values!");

    std::for_each(seq.values.begin(), seq.values.end(),
                  [](const compile_constructible& value) {
                    // std::cout << value.m_one << " " << value.m_two << "\n";
                  });
  }

  return 0;
}
