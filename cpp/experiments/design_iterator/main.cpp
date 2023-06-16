#include <algorithm>
#include <iostream>
#include <vector>

namespace task {

struct iterator_args {
  std::vector<int> one;
  std::vector<int> two;
  std::vector<int> three;
};

struct validity_wrapper {
  int current;
  // Even value from odd list is valid.
  // Odd value from even list is valid.
  bool is_valid;
};

bool is_even(const int value) { return value % 2 == 0; }

bool is_odd(const int value) { return value % 2 != 0; }

// Lambdas are anonymous functions and they are plenty usefull in
// JavaScript.
//
// I wasn't sure how to preserve state between function calls and I had a hunch
// I could use lambda because they are useful in javascript. I wanted to use
// something similar to IIFE in JavaScript, but couldn't come up with an idea.
// I saw on google a list of ideas (no solution!) how to preserve state, answer:
// lambda. That's when it hit me... Lambda is a class with overloaded operator()
// and I knew I could save some state inside an object!
class iterator {
 private:
  const std::size_t m_initial_index{0};

  const std::size_t m_pointer_accessor_one{0};
  const std::size_t m_pointer_accessor_two{1};
  const std::size_t m_pointer_accessor_three{2};

  std::vector<std::size_t> m_pointer{m_initial_index, m_initial_index,
                                     m_initial_index};

  struct component {
    // This could be improved because we always create a copy of a list which
    // degrades performance. I tried to use a smart pointers and references, but
    // the compiler complains.
    // Reference members cause error because move assignment is deleted.
    // Smart pointers, I don't know how to use them.
    std::vector<int> list;
    std::size_t pointer_accessor;
    bool is_out_of_bounds;
  };

  void m_next(const std::size_t pointer_accessor) {
    ++m_pointer.at(pointer_accessor);
  }

  int m_access_list_value(const std::vector<int>& list,
                          const std::size_t pointer_accessor) const {
    std::size_t index{m_pointer.at(pointer_accessor)};
    return list.at(index);
  }

  struct validity_checker_args {
    const std::size_t pointer_accessor;
    const int retrieved_value;
  };

  bool m_is_retrieved_value_valid(const validity_checker_args& args) const {
    // Zero and Two are considered even values, but we enumerate lists from 1
    // onwards. The simplest solution I figured was to use this function as
    // abstraction to encapsulate that logic.
    if (args.pointer_accessor == m_pointer_accessor_one ||
        args.pointer_accessor == m_pointer_accessor_three) {
      // Even number from odd list is valid.
      return is_even(args.retrieved_value);
    }
    if (args.pointer_accessor == m_pointer_accessor_two) {
      // Odd number from even list is valid.
      return is_odd(args.retrieved_value);
    }

    throw std::runtime_error(
        "Comparison of pointer accessor failed. Received unhandled value.");
  }

  validity_wrapper m_choose_smallest(const iterator_args& _iterator_args) {
    // Lists are of variadic length and synchronisation of which pointer to use
    // on which list plus checking for list boundaries was kind of painful.
    // Hence the solution to variadic length of lists, which lists are remaining
    // and which lists I can access are solved using an array which allows me
    // not to worry if a value pointer is attempting to access value that's out
    // of lists bounds. We have to store the pointer accessor because once the
    // lists are filtered out, we have no way to know which list out of the 3
    // are remaining because none of them are marked.
    std::vector<component> exclude_out_of_bounds{
        {_iterator_args.one, m_pointer_accessor_one,
         _iterator_args.one.size() == m_pointer.at(m_pointer_accessor_one)},
        {_iterator_args.two, m_pointer_accessor_two,
         _iterator_args.two.size() == m_pointer.at(m_pointer_accessor_two)},
        {_iterator_args.three, m_pointer_accessor_three,
         _iterator_args.three.size() == m_pointer.at(m_pointer_accessor_three)},
    };

    exclude_out_of_bounds.erase(
        std::remove_if(exclude_out_of_bounds.begin(),
                       exclude_out_of_bounds.end(),
                       [](const component& _component) {
                         return _component.is_out_of_bounds;
                       }),
        exclude_out_of_bounds.end());

    constexpr std::size_t empty{0};
    bool has_no_retrievable_values{exclude_out_of_bounds.size() == empty};
    if (has_no_retrievable_values) {
      // If we don't have retrievable values, it should be safe to exit and
      // ignore incrementing the value pointer because if we are in this place,
      // all of them should point to invalid value anyway.

      constexpr bool is_valid{false};
      const validity_wrapper lists_are_empty{done, is_valid};

      return lists_are_empty;
    }

    // Comparing 3 values is the same as doing linear search for smallest value
    // to which each pointer points to.
    const auto _component{std::min_element(
        exclude_out_of_bounds.begin(), exclude_out_of_bounds.end(),
        [this](const component& current, const component& min) {
          return m_access_list_value(current.list, current.pointer_accessor) <
                 m_access_list_value(min.list, min.pointer_accessor);
        })};

    const int current_value{
        m_access_list_value(_component->list, _component->pointer_accessor)};

    m_next(_component->pointer_accessor);

    // This is the last location where we know a list from which the value has
    // been retrieved.
    const validity_checker_args accessed_from_list{_component->pointer_accessor,
                                                   current_value};
    const bool is_valid{m_is_retrieved_value_valid(accessed_from_list)};

    const validity_wrapper current{current_value, is_valid};
    return current;
  }

 public:
  static const int done{-1};

  int operator()(const iterator_args& _iterator_args) {
    // Loop is necessary because we are not guaranteed to retrieve a value from
    // O(1) call. When all lists contain only invalid elements, one call takes
    // O(3 * n) time to retrieve the valid one which doesn't exist.
    while (true) {
      const validity_wrapper smallest{m_choose_smallest(_iterator_args)};
      if (smallest.is_valid) {
        return smallest.current;
      }
      // When we are done the value is always in invalid state.
      if (smallest.current == done) {
        return done;
      }
    }
  }
};

}  // namespace task

namespace test {

namespace runner {

// Make naming exception to make it consistent with the task requirements.
void dump_iterator(std::ostream& _ostream, const task::iterator_args& lists,
                   task::iterator GetNext) {
  auto value = GetNext(lists);
  while (value != task::iterator::done) {
    _ostream << value << "\n";
    value = GetNext(lists);
  }
}

}  // namespace runner

namespace data {
namespace task_input {

task::iterator_args create_data() {
  const std::vector<int> one{1, 8, 15, 16, 35};
  const std::vector<int> two{2, 7, 12, 63};
  const std::vector<int> three{10, 13, 14, 42};

  task::iterator_args lists{one, two, three};

  return lists;
}

}  // namespace task_input

namespace all_valid {

task::iterator_args create_data() {
  const std::vector<int> one{2, 6, 10, 14};
  const std::vector<int> two{3, 7, 11, 15};
  const std::vector<int> three{4, 8, 12, 16};

  task::iterator_args lists{one, two, three};

  return lists;
}

}  // namespace all_valid

namespace one_last_valid {

task::iterator_args create_data() {
  const std::vector<int> one{1, 5, 9, 13, 2};
  const std::vector<int> two{2, 4, 6, 8, 10};
  const std::vector<int> three{3, 7, 11};

  task::iterator_args lists{one, two, three};

  return lists;
}

}  // namespace one_last_valid
}  // namespace data
}  // namespace test

int main() {
  const std::string separator{"--------\n"};

  test::runner::dump_iterator(std::cout, test::data::task_input::create_data(),
                              task::iterator{});
  std::cout << separator;
  test::runner::dump_iterator(std::cout, test::data::all_valid::create_data(),
                              task::iterator{});
  std::cout << separator;
  test::runner::dump_iterator(
      std::cout, test::data::one_last_valid::create_data(), task::iterator{});

  return 0;
}
