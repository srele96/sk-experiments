/**
 * Through these examples I have learned why priority_queue couldn't take in
 * example::way_one::edge. The overloaded operator had body which can mutate the
 * state.
 *
 * In simple words, if we were to freeze me at my current time, let's say my
 * name is John, age is 25. Let's say we want to freeze me with these values for
 * name and age. You are allowed to take information from me, but you aren't
 * allowed to change my age or name, because i am frozen. If I were to
 * tell_name() to you, who will guarantee that my name isn't changed by that
 * behavior? We all know that me telling you my name is not going to change it,
 * but who guarantees? Well, someone has to. For us, it is our experience and
 * common sense, we know that me telling my name won't change it. When it comes
 * to C++ the program has no experience or common sense. Therefore we have to
 * make sure to make that guarantee. The way we make a guarantee is by saying
 * `const` before the body of behavior we want to protect. If we want to
 * guarantee that my name won't be changed if i tell it to you, we do it like
 * this:
 *
 * struct Me {
 *   int age;
 *
 *   int tell_age() const { return age; }
 * };
 *
 * See that const? That is guarantee that there are no changes.
 */

#include <iostream>

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

namespace non_mutable_getter {

namespace incorrect {

struct person {
  int age;

  int get_age() { return age; }
};

void use_get_age() {
  const int age{25};
  const person jim{age};

  std::cout << jim.get_age();  // Error, get age may change age
}

}  // namespace incorrect

namespace correct {

struct person {
  int age;

  int get_age() const { return age; }
};

void use_get_age() {
  const int age{25};
  const person jim{age};

  std::cout << jim.get_age();  // Ok
}

}  // namespace correct

}  // namespace non_mutable_getter

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

namespace example {

namespace way_one {

struct edge {
  int endpoint_one;
  int endpoint_two;
  int weight;

  // Later I found out the problem here is that the problem is missing const
  // identifier
  bool operator<(const edge& other) { return weight < other.weight; }
  bool operator>(const edge& other) { return weight > other.weight; }
};

}  // namespace way_one

namespace way_two {

struct edge {
  int endpoint_one;
  int endpoint_two;
  int weight;

  friend bool operator<(const edge& lval, const edge& rval) {
    return lval.weight < rval.weight;
  }
  friend bool operator>(const edge& lval, const edge& rval) {
    return lval.weight > rval.weight;
  }
};

}  // namespace way_two

namespace way_three {

struct edge {
  int enpoind_one;
  int endpoint_two;
  int weight;
};

bool operator<(const edge& lval, const edge& rval) {
  return lval.weight < rval.weight;
}

bool operator>(const edge& lval, const edge& rval) {
  return lval.weight > rval.weight;
}

}  // namespace way_three

}  // namespace example

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

namespace compare_edges {

namespace non_constants {

void way_one() {
  example::way_one::edge one{1, 2, 3};
  example::way_one::edge two{1, 3, 4};
  bool one_is_smaller = one < two;
  std::cout << "Way one: " << one_is_smaller << "\n";
}

void way_two() {
  example::way_two::edge one{1, 2, 3};
  example::way_two::edge two{1, 3, 4};
  bool one_is_smaller = one < two;
  std::cout << "Way two: " << one_is_smaller << "\n";
}

void way_three() {
  example::way_three::edge one{1, 2, 3};
  example::way_three::edge two{1, 2, 4};
  bool one_is_smaller = one < two;
  std::cout << "Way three: " << one_is_smaller << "\n";
}

}  // namespace non_constants

namespace constants {

void way_one() {
  const example::way_one::edge one{1, 2, 3};
  const example::way_two::edge two{1, 2, 4};
  bool one_is_smaller = one < two;
  std::cout << "Way one: " << one_is_smaller << "\n";
}

void way_two() {
  const example::way_two::edge one{1, 2, 3};
  const example::way_two::edge two{1, 3, 4};
  bool one_is_smaller = one < two;
  std::cout << "Way two: " << one_is_smaller << "\n";
}

void way_three() {
  const example::way_three::edge one{1, 2, 3};
  const example::way_three::edge two{1, 2, 4};
  bool one_is_smaller = one < two;
  std::cout << "Way three: " << one_is_smaller << "\n";
}

}  // namespace constants

}  // namespace compare_edges

// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

int main() {
  compare_edges::non_constants::way_one();
  compare_edges::non_constants::way_two();
  compare_edges::non_constants::way_three();

  compare_edges::constants::way_one();
  compare_edges::constants::way_two();
  compare_edges::constants::way_three();

  non_mutable_getter::correct::use_get_age();
  non_mutable_getter::incorrect::use_get_age();

  return 0;
}
