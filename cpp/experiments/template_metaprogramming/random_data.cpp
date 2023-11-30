/******************************************************************************
*******************************************************************************

Problem: Mixed Data Processing

Problem Description:

You are given a sequence of operations to perform on a list of mixed data types.
The data types can include integers, strings, and floating-point numbers. Each
operation will specify the type of data it should be applied to and a specific
action to perform. Your task is to process these operations efficiently using
type erasure in C++.

Operations:

    Add Data: Adds a new element of a specified type (int, string, or float) to
the list. Process Data: Applies a specified action to all elements of a
particular type in the list. Actions can include: For integers: Add a specified
value to each integer. For strings: Append a specified substring to each string.
        For floats: Multiply each float by a specified value.

Input:

    The first line contains an integer NN (1 ≤ NN ≤ 10^5), the number of
operations. The next NN lines describe the operations. Each line starts with an
operation type ("Add" or "Process"), followed by the data type ("int", "string",
"float"), and then the operation-specific data.

Output:

    After processing all operations, output the final list of elements in the
order they were added, one element per line.

Example:

Input:


6
Add int 5
Add string hello
Add float 3.5
Process int 2
Process string world
Process float 1.5

Output:

7
helloworld
5.25

Explanation:

    The first three operations add an integer (5), a string ("hello"), and a
float (3.5) to the list. The fourth operation adds 2 to the integer, making
it 7. The fifth operation appends "world" to the string, making it "helloworld".
    The sixth operation multiplies the float by 1.5, making it 5.25.

This problem will test your ability to implement type erasure in C++ to handle
different data types in a single list and perform type-specific operations
without resorting to explicit casting or type checking at runtime.

*******************************************************************************
******************************************************************************/

#include <iostream>
#include <memory>
#include <vector>

// Type erasure depends on behavior, polymorphism depends on interface.
//
// Standard library std::function requires type to be callable.
//
// How do we require the type to behave?
//
// A container which can perform behavioral check if it's the correct type and
// which is able to process the data.

// Honestly this is quite shitty problem to solve using type erasure as we do
// not have absolutely any benefit from anonymous type. The problem could have
// been solved using the following struct:
//
// struct foo {
//   std::string type;
//   std::string value;
//   void process(const std::string&, const std::string&);
// };
//
// The beauty of std::function is that it's a type that only checks if provided
// type is callable, the end. The type erasure is beautiful when it performs a
// type checking on the type it holds and asserts that it can behave in certain
// way. For example, it can contain any type that is:
// - processable
// - serializable
// - destructible
// - move constructible
//
// Basically I think I can see the type erasure as a way to hold a type and
// assert that it's able to do certain things. I think that is really good
// perspective. It is much better than confusion that I held before.
//
// From that perspective if we have a type object_ which can contain any type
// that can `void process(const std::string&, const std::string&)` then we could
// create three different types.
//
// integer_
// string_
// float_
//
// Each of them would be able to process the data in a different way.
// Actually each of them would receive the std::string and it would know how to
// process it.
//
// The problem that is probably solvable out of the scope of this problem is how
// to avoid processing unrelated types. For example, it seems stupid for
// integer_ to receive the type string because it already knows its own type.
//
// The thing is, type erasure is used exactly for that. We treat all processable
// types as the same type. However we could could still keep the generality by
// saying that a processable type holds a type T and a string that labels it. I
// do not know of a pretty way to skip a type, its actually stupid that we want
// to do the type check at all on the processable. Therefore that information
// should be held outside of it. We could store the pairs of information such as
// [type, processable] and for each of them, if type matches, we could process
// the string value. The beauty is that we can declare the processable types
// outside of type erasure. Now that I think of it, we are erasing all type
// information and performing compile time checks on the type we hold.
//
// I wonder if it's valid for type erased type to use different overloads of the
// same method. However that overload expects a concrete type.

// Explanation of what I think happens
//
// The object contains a shared pointer to a concept.
// A concept is an interface which defines the polymorphic behavior.
//
// Actually, an object defines public interface of what's possible to do with
// any type it contains. How does it achieve that?
//
// First it contains a shared pointer to a concept, which allows runtime
// polymorphic behavior. At compile time the type is replaced with concrete
// type. So the combination of runtime polymorphism and compile time duck typing
// we implement the type erasure.
//
// A public interface on the object calls the methods of the concept, which
// allows runtime polymorphism.
//
// We create a concrete model of a concept, but it's handled through the base
// class pointer.
//
// The construction of an object knows a concrete type that it will hold a
// pointer to. The concrete type can be any class, why? Because we create a
// shared pointer of a model, which is our implementation, which contains a duck
// types T that receives an object as well.
//
// So now a model of T contains concrete type, for example `integer_`. A model
// holds a type of `integer_` and just straight away calls its methods. However
// it calls its methods at runtime through the base class pointer.
//
// I still don't know which part fails at compile time if the method is not
// defined. I assume that if compiler sees an object duck typed replaced, aha...
// it then fails.
//
// For example:
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// struct foo {
//   template <typename T>
//   foo(T p_object) {
//     p_object.process("hello");
//   }
// };
//
// struct bar {
//   void process(const std::string& p_value) { std::cout << p_value << "\n"; }
// };
//
// struct baz {};
//
// foo f{bar{}};
// foo b{baz{}}; // Fails at compile time.
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// That is completely valid code, where the type T at compile time expects to
// have a method `process`.

// At which point does it erase the type information?
// We are using the type T through the object_ class. The object_ class contains
// explicitly defined methods and we can only call those.

// Why do we need interface at all?
// It looks like we do not need them because we can take the type T and hold it
// inside and only call the methods that we need.
//
// Wrong. The class does not know the type that it holds. It only knows about
// the concept. The class through constructor takes any type and holds any type
// inside the model. We are utilizing the templated constructor to take any
// type, hold that type inside the model, and we call models methods. Model
// calls the types methods. The trick we use is that we always hold the same
// type inside the object, while the model utilizes the holding of one concrete
// type and calls it through duck typing. At runtime templates are what?
// Constructors are specialized at compile time. So now we have a class that may
// contain A, B, C, D within the model.
// Through this we have a container which holds a model which holds any type.

// Source
// https://www.modernescpp.com/index.php/type-erasure/

class object_ {
 private:
  struct concept_ {
    virtual void process(const std::string& p_value) = 0;
    virtual void out(std::ostream& p_ostream) const = 0;

    virtual ~concept_() = default;
  };

  template <typename T>
  struct model_ : concept_ {
    model_(const T& p_object) : m_object{p_object} {}

    void process(const std::string& p_value) override {
      m_object.process(p_value);
    }

    void out(std::ostream& p_ostream) const override {
      m_object.out(p_ostream);
    }

    T m_object;
  };

  std::shared_ptr<concept_> m_object;

 public:
  template <typename T>
  object_(T&& p_object)
      : m_object{std::make_shared<model_<T>>(std::forward<T>(p_object))} {}

  // So any object_ is only processable, and that's it? Did I get it right?
  void process(const std::string& p_value) { m_object->process(p_value); }
  void out(std::ostream& p_ostream) const { m_object->out(p_ostream); }
};

class integer_ {
 private:
  int m_value;

 public:
  integer_(const std::string& p_value) : m_value{std::stoi(p_value)} {}

  void process(const std::string& p_value) { m_value += std::stoi(p_value); }
  void out(std::ostream& p_ostream) const { p_ostream << m_value << "\n"; }
};

class string_ {
 private:
  std::string m_value;

 public:
  string_(const std::string& p_value) : m_value{p_value} {}

  void process(const std::string& p_value) { m_value += p_value; }
  void out(std::ostream& p_ostream) const { p_ostream << m_value << "\n"; }
};

class float_ {
 private:
  float m_value;

 public:
  float_(const std::string& p_value) : m_value{std::stof(p_value)} {}

  void process(const std::string& p_value) { m_value *= std::stof(p_value); }
  void out(std::ostream& p_ostream) const { p_ostream << m_value << "\n"; }
};

int main() {
  int t;
  std::cin >> t;

  std::vector<std::pair<std::string, object_>> pairs;

  while (t-- > 0) {
    // Doesn't matter as long as it produces the expected output.
    std::string operation, type, value;
    std::cin >> operation >> type >> value;

    if (operation == "Add") {
      if (type == "int") {
        pairs.push_back({"int", integer_{value}});
      } else if (type == "string") {
        pairs.push_back({"string", string_{value}});
      } else if (type == "float") {
        pairs.push_back({"float", float_{value}});
      }
    } else if (operation == "Process") {
      for (auto& pair : pairs) {
        if (pair.first == type) {
          pair.second.process(value);
        }

        // Questions from the state of confusion:
        //
        // How should the generic container process the data?
        // How should the public API look like?
      }
    }
  }

  for (const auto& pair : pairs) {
    pair.second.out(std::cout);
  }
}
