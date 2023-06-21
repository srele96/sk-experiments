#include <iostream>
#include <vector>

// The differences between these initializers are as follows:
//
//   1. std::vector<std::vector<char>> first; This initializes an empty
// std::vector of std::vector<char> objects.
//
//   2. std::vector<std::vector<char>> second{}; This also initializes an empty
// std::vector of std::vector<char> objects. The curly braces are optional and
// have the same effect as not using them at all.
//
//   3. std::vector<std::vector<char>> third{{}}; This initializes a std::vector
// of std::vector<char> objects with a single element, which is an empty
// std::vector<char>.
//
//   4. std::vector<std::vector<char>> fourth{{}, {}}; This initializes a
// std::vector of std::vector<char> objects with two elements, both of which are
// empty std::vector<char> objects.
//
//   5. std::vector<std::vector<char>> fifth{{'C'}}; This initializes a
// std::vector of std::vector<char> objects with a single element, which is a
// std::vector<char> containing a single character 'C'.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Q: why are the curly braces optional in the first two cases? i thought it is
// better to use initializer list
//
// The curly braces are optional in the first two cases because they are used to
// specify an initializer list, and an initializer list is not required to
// initialize the std::vector objects in these cases.
//
// An initializer list is a list of values enclosed in curly braces, and it is
// used to specify the initial values for an object. For example, the following
// code uses an initializer list to initialize a std::vector with three
// elements: std::vector<int> v{1, 2, 3};
//
// If an initializer list is not provided, the std::vector will be
// default-initialized, which means that it will be constructed with an empty
// list of elements. This is the case in the first two examples you provided.
//
// In general, it is a good practice to use an initializer list when it is
// appropriate, because it can make your code more readable and efficient.
// However, it is not always necessary to use an initializer list, and in these
// cases it is fine to omit the curly braces.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Q: how do i know if i can omit initializer list?
//
// You can omit an initializer list if the object being initialized has a
// default constructor, and you do not need to specify any initial values for
// the object.
//
// For example, you can omit an initializer list when initializing a std::vector
// or a std::string object, because these types have default constructors that
// create an empty object. Similarly, you can omit an initializer list when
// initializing a built-in type (such as an int or a float) if you do not need
// to specify an initial value for the object.
//
// Here are some examples of initializations where the initializer list can be
// omitted:
//
// std::vector<int> v;            // Initializes an empty vector
// std::string s;                 // Initializes an empty string
// int x;                         // Initializes x to 0 (the default value for
// int)
//
// On the other hand, if you need to specify initial values for an object, or if
// the object does not have a default constructor, you must use an initializer
// list.
//
// For example, the following initializations require an initializer list:
//
// std::vector<int> v{1, 2, 3};  // Initializes a vector with three elements
// std::string s{"hello"};       // Initializes a string with the value "hello"
// int x{10};                    // Initializes x to 10
//
// Overall, the decision of whether or not to use an initializer list when
// initializing an object depends on the type of the object and whether or not
// you need to specify initial values for the object.
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Q: why does default constructor allow me to omit initializer list?
//
// A default constructor is a constructor that can be called with no arguments
// (or with default values for all arguments). It is used to create an object
// with default-initialized values.
//
// If an object has a default constructor, you can omit the initializer list
// when initializing the object, because the default constructor will be called
// to create the object with default-initialized values.
//
// For example, the std::vector and std::string types both have default
// constructors that create an empty object, so you can omit the initializer
// list when initializing these types:
//
// std::vector<int> v;            // Initializes an empty vector
// std::string s;                 // Initializes an empty string
//
// On the other hand, if an object does not have a default constructor, or if
// you need to specify initial values for the object, you must use an
// initializer list to specify the values.
//
// For example, the following initializations require an initializer list:
//
// std::vector<int> v{1, 2, 3};  // Initializes a vector with three elements
// std::string s{"hello"};       // Initializes a string with the value "hello"
//
// Overall, the decision of whether or not to use an initializer list when
// initializing an object depends on the type of the object and whether or not
// you need to specify initial values for the object.

int main() {
  // What are the differences between these initializers?
  std::vector<std::vector<char>> first;
  std::vector<std::vector<char>> second{};
  std::vector<std::vector<char>> third{{}};
  std::vector<std::vector<char>> fourth{{}, {}};
  std::vector<std::vector<char>> fifth{{'C'}};

  // Figure out the differences.
  std::cout << "first: " << first.size() << '\n';
  std::cout << "second: " << second.size() << '\n';
  std::cout << "third: " << third.size() << ' ' << third.at(0).size() << '\n';
  std::cout << "fourth: " << fourth.size() << ' ' << fourth.at(0).size() << ' '
            << fourth.at(1).size() << '\n';
  std::cout << "fifth: " << fifth.size() << ' ' << fifth.at(0).size() << ' '
            << fifth.at(0).at(0) << '\n';

  return 0;
}
