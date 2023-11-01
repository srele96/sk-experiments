#include <algorithm>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <typeinfo>
#include <utility>
#include <variant>
#include <vector>

namespace curiously_recurring_template_pattern {

namespace a {

template <class T>
class base {
 public:
  // void interface() { static_cast<T*>(this)->implementation(); }
  void sth() { static_cast<T*>(this)->implementation(); }

  void implementation() { std::cout << "Base implementation.\n"; }
};

class derived : public base<derived> {
 private:
  const int m_initial_x{5};
  int m_x{m_initial_x};

 public:
  void implementation() const {
    std::cout << "Derived implementation: " << m_x << "\n";
  }
};

}  // namespace a

namespace b {

class base {
 public:
  void interface() { implementation(); }
  void implementation() { std::cout << "Base implementation\n"; }
};

class derived : public base {
 public:
  void implementation() { std::cout << "Derived implementation\n"; }
};

}  // namespace b

// Does it work if the derived override the interface method?
namespace c {

template <class T>
class base {
 public:
  void interface() { static_cast<T*>(this)->implementation(); }

  void implementation() { std::cout << "Base implementation.\n"; }
};

class derived : public base<derived> {
 private:
  const int m_initial_x{5};
  int m_x{m_initial_x};

 public:
  void implementation() const {
    std::cout << "Derived implementation: " << m_x << "\n";
  }

  void interface() { std::cout << "Derived interface\n"; }
};

}  // namespace c

namespace d {

class base {
 public:
  void implementation() { std::cout << "Base implementation\n"; }
};

class derived : public base {
 public:
  //  Ok without pointers. Not ok with pointers. Does not override correctly at
  //  runtime.
  void implementation() { std::cout << "Derived implementation\n"; }
};

}  // namespace d

namespace e {

class base {
 public:
  virtual void implementation() { std::cout << "Base implementation\n"; }
};

class derived : public base {
 public:
  // Now I understand. Virtual methods are for runtime polymorphism.
  // The CRTP is for compile time polymorphism.
  void implementation() override { std::cout << "Derived implementation\n"; }
};

}  // namespace e

// ----------------------------------------------------------------------------
// User
//
// is CRTP used ONLY for compile time polymorphism?
// ----------------------------------------------------------------------------
// ChatGPT
//
// The Curiously Recurring Template Pattern (CRTP) is primarily known and used
// for achieving static (compile-time) polymorphism in C++, but it's not its
// only use. While the main advantage of CRTP is indeed to provide a way for
// base classes to use methods of derived classes during compile time, thus
// avoiding the overhead of dynamic polymorphism (virtual functions and
// vtables), there are other uses and benefits of this pattern. Here are a few:
//
//     Compile-Time Polymorphism: This is the most common use of CRTP. It allows
//     the compiler to determine the correct function to call at compile time,
//     avoiding the runtime overhead of virtual methods.
//
//     Providing Base Class Methods: CRTP can be used to provide default
//     implementations of methods in the base class that can work for all
//     derived classes, without requiring virtual functions.
//
//     Code Reuse: It can help avoid duplicating code across several classes by
//     using a common template base class.
//
//     Enforcing Interface Compliance: Similar to providing base class methods,
//     CRTP can enforce that derived classes implement certain methods, again
//     without the overhead of virtual methods.
//
//     Type Traits and Type Information: CRTP can be used to provide
//     compile-time type information about the derived classes without using
//     RTTI (Runtime Type Information), by giving the base class a way to access
//     the type of the derived class.
//
//     Mixin-style Composition: CRTP can be used to implement mixin-style
//     composition, allowing classes to inherit behaviors from a variety of
//     sources while avoiding multiple inheritance issues.
//
//     Method Chaining with Covariant Return Types: CRTP enables method chaining
//     while preserving covariant return types across inherited classes,
//     something that's not possible with regular polymorphism.
//
// While CRTP is a powerful tool, it's worth noting that it can make code more
// complex and harder to read, and it doesn't quite replace the need for dynamic
// polymorphism in scenarios where objects of different classes need to be
// handled polymorphically at runtime. It's a tool in a programmer's toolkit, to
// be used when appropriate.
// ----------------------------------------------------------------------------
// wait....
//
// MAIN advantage is that BASE class can call DERIVED class method????? combined
// with compile time polymorphism??? now it makes sense!!!!
// ----------------------------------------------------------------------------
// ChatGPT
//
// Yes, exactly! The main advantage of the Curiously Recurring Template Pattern
// (CRTP) is that it allows the base class to call methods from the derived
// class at compile time, effectively achieving compile-time polymorphism
// without the overhead of virtual function calls and the need for a vtable that
// comes with runtime polymorphism.
//
// This is made possible because, with CRTP, the derived class is passed as a
// template parameter to the base class. This means the base class "knows" the
// type of the derived class at compile time and can therefore use its methods.
// This pattern allows for method overriding and other operations that are
// typically associated with runtime polymorphism, but without its performance
// cost.
// ----------------------------------------------------------------------------

namespace f {

template <class T>
class base {
 public:
  // First create the base class and then just assume we know which methods
  // child class has and call it.

  void a() { static_cast<T*>(this)->b(); }
};

class derived_a : public base<derived_a> {
 public:
  void b() { std::cout << "b\n"; }
};

}  // namespace f

// Allow every logger implementation to call .log method without `virtual`
// overhead.
//
// I kept failing to see the
//  - Benefits of the CRTP
//  - Use case of the CRTP
//  - Situations where I can use the CRTP
//
// The problem where I could call one method on multiple objects of different
// type was already familiar to me. I mapped them together and that's when I
// understood.
namespace logger {

template <class T>
class base {
 public:
  // ----------------------------------------------------------------------------
  // User
  //
  // how cna i print the type? can i somehow get a type and print it in std
  // cout?
  //
  // Im interested in this:
  //
  // void log(std::ostream& ostream) { static_cast<T*>(this)->log_impl(ostream);
  // }
  //
  // I'm interested about this part
  //
  // static_cast<T*>(this)
  //
  // it casts this pointer to pointer T, which will generate code at compilation
  // time which casts
  //
  // static_cast<info*>(this)->log_impl(ostream);
  //
  // and since the `info` class is declared and defined, it will use that class
  // even inside the base class? so aha... i see, it's a trick, to use compile
  // time generation to generate code, clever, cool
  //
  // ----------------------------------------------------------------------------
  // ChatGPT
  //
  //  Yes, your understanding is correct. The CRTP is indeed a compile-time
  //  technique that leverages templates to enable a base class to call methods
  //  from a derived class. This is possible because, at compile time, the
  //  specific derived class is known due to the template parameter, and
  //  static_cast safely converts the this pointer to a pointer of the derived
  //  type.
  // ----------------------------------------------------------------------------
  void log(std::ostream& ostream) { static_cast<T*>(this)->log_impl(ostream); }
};

class info : public base<info> {
 public:
  void log_impl(std::ostream& ostream) { ostream << "info\n"; }
};

class warn : public base<warn> {
 public:
  void log_impl(std::ostream& ostream) { ostream << "warn\n"; }
};

class error : public base<error> {
 public:
  void log_impl(std::ostream& ostream) { ostream << "error\n"; }
};

// ----------------------------------------------------------------------------
// I fail to see the benefits of the CRTP.
//
// Each derived class can simply implement the log method and it would also
// work.
//
// Why would I need the CRTP in this case?
// ----------------------------------------------------------------------------
// ChatGPT
//
// The example you've provided is indeed a situation where you could use CRTP,
// but it also highlights an important point about when using CRTP is
// advantageous.
//
// In your logger example, base is a class template that defines a log() method.
// This method calls log_impl(), which is expected to be provided by the derived
// classes (info, warn, error). This is a classic use of CRTP: the base class
// defines some general behavior (log()) and relies on the derived class to
// provide specific behavior (log_impl()).
//
// However, you're correct in your comment that in this particular case, each
// derived class could simply implement its own log() method directly, without
// any need for CRTP. This is because there's no common behavior that's being
// shared between the different log() methods.
//
// The power of CRTP is more evident when there is common behavior that should
// be shared between different implementations or when there is a need for base
// class methods that rely on functionality provided by derived classes. If your
// log() method in the base class did something more complex that was the same
// for info, warn, and error, and you wanted to avoid duplicating that code in
// each derived class, that would be a good use case for CRTP.
//
// For example, suppose that in addition to logging the message, you wanted to
// add a timestamp to every log entry, and the process of getting and formatting
// the timestamp is the same for info, warn, and error. By using CRTP, you could
// implement the timestamp functionality once in your base class and still have
// info, warn, and error provide their own specific logging behaviors.
// ----------------------------------------------------------------------------
//
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------
// ------------------------------- NOTE!!! BEGIN ------------------------------
//
// It seems I must ask multiple complementary questions for the topic to make
// sense.
// Only after I thought I understood the CRTP I realized I don't.
// I understood that I can see the base class as if it could share the
// implementation between objects.
// I didn't understand why would I do that if simply each method would have the
// same name.
// Then I realized that reusability of the same functionality that each method
// depends on was the key.
//
// ------------------------------- NOTE!!! END --------------------------------
// ----------------------------------------------------------------------------
// ----------------------------------------------------------------------------

}  // namespace logger

namespace crtp_static_method {

// is there even a need for crtp when calling child static method? it can still
// reuse the functionality between derived classes, but it feels different now?
// ----------------------------------------------------------------------------
// However, as you've pointed out, when you're only dealing with static methods,
// the entire setup might feel a bit contrived. After all, if you're not making
// use of instance-specific behavior, then the need to use inheritance at all
// becomes debatable. Instead, one might argue for a more modular or
// traits-based approach where shared behavior is defined in utility classes or
// functions, and individual types aggregate or use these utilities as needed.
//
// The CRTP shines when you want to mix instance-specific behavior of derived
// classes with shared functionality in a base class, leveraging the
// compile-time polymorphism it offers. If you're only using static methods,
// then you're right: the benefits of CRTP in such a context may seem
// diminished.

template <class derived>
class base {
 public:
  // ----------------------------------------------------------------------------
  // i don't quite understand why does method marked const require me to cast
  // this to const derived*?
  //
  // the const method means it doesn't modify the value it points to... however
  // the cast to pointer ah... i think i see, does it mean
  //
  // method is marked as const, it can only call const methods
  //
  // we call methods through this pointer, the type of pointer determines which
  // methods we can call, if this pointer is non const, it can call non const
  // methods, if this pointer is const, it can not call non const methods?
  //
  // ----------------------------------------------------------------------------
  //
  // Yes, you're on the right track. Let me elaborate further:
  //
  //     const Member Function: When a member function is marked as const, it
  //     means that it promises not to modify the state of the object on which
  //     it is called. In other words, it cannot modify any data members and can
  //     only call other const member functions.
  //
  //     this Pointer: Inside a member function, the this pointer is an implicit
  //     pointer that points to the object on which the member function is
  //     called. The type of the this pointer is:
  //         T* const inside non-const member functions of class T.
  //         const T* const inside const member functions of class T.
  //
  //     This means that in a const member function, the this pointer points to
  //     a const object, ensuring the function doesn't modify the object.
  //
  //     Static Casting: When you do a static_cast, you're explicitly
  //     instructing the compiler to treat the expression in a certain way. If
  //     you try to static_cast a const pointer to a non-const pointer, you're
  //     attempting to remove the const-ness. This is not allowed because it
  //     violates the promise of const-correctness.
  //
  // So in the context of your log function, since it's marked const, the this
  // pointer is of type const base<derived>*. When you do the static_cast, you
  // need to cast to a pointer that is also const to match the type and the
  // promises you've made via the const qualifier.
  //
  // Your understanding in the latter part of your question is correct. The type
  // of the this pointer determines which methods you can call. If it's a const
  // pointer, you can only call const methods on it. If it's a non-const
  // pointer, you can call any method.
  // ----------------------------------------------------------------------------

  // OK
  // void log() noexcept { static_cast<derived*>(this)->log_impl(); }

  // NOK
  // void log() const noexcept { static_cast<derived*>(this)->log_impl(); }

  // OK
  void log() const noexcept {
    static_cast<const derived*>(this)->log_impl(
        " static_cast<const derived*>(this)->log_impl(/* ... */);\n");
  }

  void log_static() const noexcept {
    derived::log_impl(" derived::log_impl(/* ... */);\n");
  }
};

class derived : public base<derived> {
 public:
  static void log_impl(const std::string& label) noexcept {
    std::cout << "derived:" << label;
  }
};

}  // namespace crtp_static_method

}  // namespace curiously_recurring_template_pattern

// A template takes type as a parameter and inside a class we can instantiate a
// value of the type parameter. Which means we can copy, move, assign, etc.
//
// We can perform various operations on the type parameter.
namespace template_parameter {

// whose responsible for calling move, destructor, copy, at runtime? at compile
// time it's compiler, but at runtime? is there code inserted to do that? or
// what?
// ----------------------------------------------------------------------------
//
// In C++, the sequence of operations, including copy/move constructors,
// destructors, and other member functions, is determined at compile-time by the
// compiler. However, the actual execution of these operations occurs at
// runtime. Here's a bit more detail:
//
//     Compile-time:
//         The compiler determines where to insert calls to constructors,
//         destructors, assignment operators, etc., based on the code you write.
//         For example, if you return a local object from a function, the
//         compiler will decide whether to use the move constructor (if it's
//         available and appropriate) or the copy constructor. Another example
//         is that the compiler inserts calls to the destructor for
//         automatic-duration objects when they go out of scope.
//
//     Runtime:
//         When the program is executed, the runtime environment (the
//         combination of the operating system, the loader, and the runtime
//         system that comes with your C++ compiler) takes care of executing the
//         machine instructions corresponding to the calls determined by the
//         compiler. The actual functions (like constructors or destructors) are
//         called, memory gets allocated or deallocated, resources are acquired
//         or released, and so forth.
//
// It's essential to understand that by "the compiler determines," we mean the
// compiler writes out machine instructions in the generated binary that
// correspond to these calls. At runtime, it's the processor executing these
// machine instructions that "calls" the appropriate functions, but the decision
// of when and where to make these calls was made by the compiler.
//
// To visualize this, you can think of the compiler as a director who writes a
// script (the machine code). In contrast, the runtime system and hardware are
// the actors who perform it, following the script's instructions.
//
// ----------------------------------------------------------------------------
//
// ah so the compiler simply puts the appropriate method of a class? if we have
//
// util::f f;
// util::f f_c = f;
//
// the compiler will insert this:
//
//
// util::f f; // default ctor
// util::f f_c = f; // copy ctor
//
// so they run at runtime, but compiler determines which one to call?
//
// ----------------------------------------------------------------------------
//
// Yes, exactly!
//
// Your C++ source code is a high-level representation of what you want the
// program to do. The compiler's job is to translate that into lower-level
// machine instructions that can be executed by the CPU.
//
// The compiler understands your intent and generates the necessary machine
// instructions to:
//
//     Call the default constructor for f.
//     Call the copy constructor for f_c using f as the argument.
//
// At runtime, the program (following the machine instructions laid out by the
// compiler) will execute those constructors in the appropriate sequence. The
// constructors' actual functionality (what they do) will then be carried out,
// such as memory allocation, setting initial values, copying values, etc.
//
// This distinction between compile-time decision making and runtime execution
// is fundamental in understanding many aspects of C++. The compiler determines
// which functions/methods to call based on the types and context, but the
// actual function's operations are executed at runtime.
// ----------------------------------------------------------------------------

template <class t>
struct f {
  t m_t;

  f() : m_t{t{}} {
    std::cout << m_t.v << "\n";

    t sth = std::move(m_t);

    std::cout << m_t.v << "\n";

    std::cout << sth.v << "\n";
  }
};

struct t {
  int v{5};

  t() { std::cout << "t()\n"; }

  t(const t& other) : v{other.v} { std::cout << "t(const t& other)\n"; }

  t& operator=(const t& other) {
    if (this != &other) {
      v = other.v;
      std::cout << "operator=(const t& other)\n";
    }

    return *this;
  }

  // Understand why does move operation require noexcept
  t(t&& other) noexcept : v{std::exchange(other.v, 0)} {
    std::cout << "t(t&& other)\n";
  }

  // Understand why does move operation require noexcept
  t& operator=(t&& other) noexcept {
    std::cout << "operator=(t&& other)\n";

    return *this;
  }

  ~t() { std::cout << "~t()\n"; }
};

void run_example() { f<t> f_t; }

}  // namespace template_parameter

namespace sfinae {

// std::enable_if_t is a type trait in C++ that is used to conditionally remove
// or enable a function or a type based on a compile-time condition. It is a
// part of the <type_traits> header. It's a shorthand for typename
// std::enable_if<B, T>::type where B is a boolean constant expression, and T is
// the type that gets enabled if B is true. If B is false, the type
// std::enable_if_t is not defined, leading to a substitution failure, which
// helps in SFINAE (Substitution Failure Is Not An Error) scenarios.
//
// Here is a simplified explanation of how std::enable_if_t works:
//
//     Conditionally Enabling Functions:
//         std::enable_if_t can be used to conditionally enable or disable
//         function overloads based on certain compile-time conditions.
//
//     Type Trait:
//         It is a template that generates a type (or nothing) based on a
//         condition.
//
//     SFINAE:
//         It is often used in conjunction with SFINAE to create template
//         specializations that are only valid under certain conditions.
//
// Here's a simple example illustrating the usage of std::enable_if_t:

template <typename E, typename T, typename = void>
struct Executor {
  // Test out variations of these assertions.
  static_assert(sizeof(E) == 0,
                "Executor requires a specialization to be used.");
};

template <typename E, typename T>
struct Executor<E, T,
                std::enable_if_t<!std::is_same_v<
                    void, decltype(std::declval<T>()(std::declval<E>()))>>> {
  static void execute(std::vector<E>& elements, T cb) {
    for (std::size_t i{0}; i < elements.size(); ++i) {
      elements[i] = cb(elements[i]);
    }
  }
};

template <typename E, typename T>
struct Executor<E, T,
                std::enable_if_t<std::is_same_v<
                    void, decltype(std::declval<T>()(std::declval<E>()))>>> {
  static void execute(std::vector<E>& elements, T cb) {
    for (std::size_t i{0}; i < elements.size(); ++i) {
      cb(elements[i]);
    }
  }
};

template <typename E, typename T>
void execute(std::vector<E>& elements, T cb) {
  Executor<E, T>::execute(elements, cb);
}

namespace template_parameter {

template <std::size_t T>
void f_size_t() {
  std::cout << "f_size_t() " << T << "\n";
}

template <bool B>
void f_bool() {
  std::cout << "f_bool() " << B << "\n";
}

template <typename T>
void f_type() {
  std::cout << "f_type() " << typeid(T).name() << "\n";
}

// a map that stored the key pair of command line argument and it's value
// the class holds the map of key/value pairs and allows user
// to retrieve the value by key and cast it to the desired type using .as<T>()

class cli_argument {
 private:
  // map of key/value pairs
 public:
  template <typename As>
  As as() {
    // parse the resource...
  }
};

template <typename As>
As as() {
  // Todo...
}

}  // namespace template_parameter

}  // namespace sfinae

namespace deduce_type {

namespace use_decltype {

struct result {
  int value;

  result() : value{1} {}
  explicit result(int p_value) : value{p_value} {}

  // Define the operators
  auto operator+(const result& other) const -> result {
    return result{value + other.value};
  }
  auto operator*(const result& other) const -> result {
    return result{value * other.value};
  }
  auto operator/(const result& other) const -> result {
    return result{value / other.value};
  }
};

struct callable_a {
  auto operator()() -> result {
    result one{1};
    result two{2};

    return one + two;
  }
};

struct callable_b {
  auto operator()() -> result {
    result one{1};
    result two{2};

    return one * two;
  }
};

template <typename T, typename E>
void typeinfo_of_decltype(
    std::ostream& ostream, T& callback_a, E& callback_b,
    const std::function<
        // Use std::variant because I don't have a way to reuse the type because
        // of decltype.
        void(const std::variant<decltype(callback_a() + callback_b()),
                                decltype(callback_a() * callback_b()),
                                decltype(callback_a() / callback_b())>&)>&
        on_result) {
  // - Can overload operators for these containers
  // - The return type of callback_a and callback_b must be what to be able to
  // do these operations?
  using type_addition = decltype(callback_a() + callback_b());
  using type_multiplication = decltype(callback_a() * callback_b());
  using type_division = decltype(callback_a() / callback_b());

  // Does typeid work on deduced type of an expression by decltype?
  ostream << typeid(decltype(callback_a() + callback_b())).name() << "\n";
  ostream << typeid(type_addition).name() << "\n";
  ostream << typeid(type_multiplication).name() << "\n";
  ostream << typeid(type_division).name() << "\n";

  const std::string separator{"  ---  \n"};
  ostream << separator;

  // Check for ambiguity: If two types within a std::variant have a common type
  // they can be converted to, assigning or emplacing can be ambiguous. To test,
  // try storing each type separately in individual variants to ensure there's
  // no ambiguity:
  //
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //
  // does variant work correctly if all 3 variants are the same type? named
  // differently?
  //
  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //
  // Yes, std::variant can hold multiple alternatives of the same type, but
  // there's an important nuance to consider.
  //
  // If you have a std::variant with multiple instances of the same type, you'll
  // have to use index-based access and emplacement, because the variant
  // wouldn't be able to distinguish between them based on type alone.
  std::variant<type_addition, type_multiplication, type_division> result;

  // What is the result's type?
  // Use default constructor of each deduced type.
  type_addition _ta;
  result.template emplace<0>(_ta);
  on_result(result);
  ostream << separator;

  type_multiplication _tm;
  result.template emplace<1>(_tm);
  on_result(result);
  ostream << separator;

  type_division _td;
  result.template emplace<2>(_td);
  on_result(result);
  ostream << separator;

  result.template emplace<0>(callback_a() + callback_b());
  on_result(result);
  ostream << separator;

  result.template emplace<1>(callback_a() * callback_b());
  on_result(result);
  ostream << separator;

  result.template emplace<2>(callback_a() / callback_b());
  on_result(result);
  ostream << separator;
}

void run() {
  callable_a callback_a;
  callable_b callback_b;

  typeinfo_of_decltype(std::cout, callback_a, callback_b,
                       // Now I have a problem to explicitly declare the type
                       // because I use decltype() to deduce type.
                       [](const auto& result) {
                         // Retrieve all variants
                         std::visit(
                             [](const auto& val) {
                               std::cout << typeid(val).name() << " -- "
                                         << val.value << "\n";
                             },
                             result);
                       });
}

}  // namespace use_decltype

namespace use_declval {

// Try it out...

}

}  // namespace deduce_type

namespace variadic_template {

template <typename T, typename... Args>
void run(std::ostream& ostream, T arg, Args... args) {
  ostream << arg;

  run(ostream, args...);
}

template <typename T, typename... Args>
void log(T t, Args... args) {
  std::cout << t << ", ";  // Print the current argument and a comma-space
  log(args...);            // Recur with the remaining arguments
}

// How does our mind go from not being able to come up with a solution
// To learning one solution, such as me learning a variadic template args
// To being able to come up with variety of different solutions
// That's a great idea to explore
// Print each Arg of Args
template <typename... Args>
void print_each_typeid_name(Args... args) {
  // ChatGPT
  //
  // The key to understanding this is to realize that the compiler is able to
  // deduce the types of the variadic arguments at compile time. This is
  // possible because the types of the arguments are known at the call site.
  //
  // For example, in your code, you're calling print_each_typeid_name with
  // arguments of type int, double, and std::string. The compiler knows this
  // because you're passing in the actual values, not variables of unknown type.
  // This means that the compiler can deduce the types of the arguments and
  // instantiate the template accordingly.
  //
  // The compiler will then generate code for each of the types in the template
  // parameter pack. In your example, it will generate code for:
  //
  //     print_each_typeid_name<int, double, std::string>(int, double,
  //     std::string);
  //
  // This is why you're seeing the typeid output for each of the types in the
  // pack.
}

// Base case
template <typename T>
void print(T t) {
  std::cout << t << "\n";
}

// Recursive case
template <typename T, typename... Args>
void print(T t, Args... args) {
  std::cout << t << " ";  // Print the current argument and a space
  print(args...);         // Recur with the remaining arguments
}

namespace resource_logger {

namespace util {

std::string ctor(const std::string& label) { return label + " - ctor\n"; }
std::string ctor_copy(const std::string& label) {
  return label + " - ctor copy\n";
}
std::string ctor_move(const std::string& label) {
  return label + " - ctor move\n";
}
std::string copy(const std::string& label) { return label + " - copy\n"; }
std::string move(const std::string& label) { return label + " - move\n"; }
std::string dtor(const std::string& label) { return label + " - dtor\n"; }
std::string print(const std::string& label) { return label + " - print\n"; }

}  // namespace util

struct a {
  a() { std::cout << util::ctor("a"); }
  a(const a& other) { std::cout << util::ctor_copy("a"); }
  a(a&& other) noexcept { std::cout << util::ctor_move("a"); }

  a& operator=(const a& other) {
    std::cout << util::copy("a");
    return *this;
  }
  a& operator=(a&& other) noexcept {
    std::cout << util::move("a");
    return *this;
  }

  ~a() { std::cout << util::dtor("a"); }

  friend std::ostream& operator<<(std::ostream& ostream, const a& a) {
    ostream << util::print("a");
    return ostream;
  }
};

struct b {
  b() { std::cout << util::ctor("b"); }
  b(const b& other) { std::cout << util::ctor_copy("b"); }
  b(b&& other) noexcept { std::cout << util::ctor_move("b"); }

  b& operator=(const b& other) {
    std::cout << util::copy("b");
    return *this;
  }
  b& operator=(b&& other) noexcept {
    std::cout << util::move("b");
    return *this;
  }

  ~b() { std::cout << util::dtor("b"); }

  friend std::ostream& operator<<(std::ostream& ostream, const b& b) {
    ostream << util::print("b");
    return ostream;
  }
};

struct c {
  c() { std::cout << util::ctor("c"); }
  c(const c& other) { std::cout << util::ctor_copy("c"); }
  c(c&& other) noexcept { std::cout << util::ctor_move("c"); }

  c& operator=(const c& other) {
    std::cout << util::copy("c");
    return *this;
  }
  c& operator=(c&& other) noexcept {
    std::cout << util::move("c");
    return *this;
  }

  ~c() { std::cout << util::dtor("c"); }

  friend std::ostream& operator<<(std::ostream& ostream, const c& c) {
    ostream << util::print("c");
    return ostream;
  }
};
}  // namespace resource_logger

template <typename... Args>
void fold(Args... args) {
  std::cout << "Fold\n";
  auto _print{[](const auto& arg) { std::cout << arg << " "; }};
  (_print(args), ...);  // Requires lambda to print space after each argument
  std::cout << "\n";
}

template <typename... Args>
void fold_ref(const Args&... args) {
  std::cout << "Fold ref\n";

  auto _print{[](const auto& arg) { std::cout << arg << " "; }};
  (_print(args), ...);

  std::cout << "\n --- \n";

  auto _print_typeid{
      [](const auto& arg) { std::cout << typeid(arg).name() << "\n"; }};
  (_print_typeid(args), ...);
}

namespace {

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// hmm its still accessible through detail namespace, what about anonymous
// namespace?
//
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//
// Yes, the detail namespace still technically makes the functions accessible,
// though it sends a clear message to developers that they shouldn't use it
// directly. If you want to further restrict access, using an anonymous
// namespace is a good idea. Functions and types inside an anonymous namespace
// have internal linkage, which means they can only be accessed within the same
// translation unit.
//
// Using an anonymous namespace in a header file with templates can be tricky
// because of how templates are instantiated. It can lead to multiple versions
// of the same function or type being generated in different translation units.
// However, since the goal here is to hide the helper function, this can be an
// acceptable trade-off.
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

template <typename T>
void pointers_counter(std::ostream& ostream, const std::size_t count,
                      T* ptr_t) {
  ostream << "(" << count << ")" << *ptr_t;
}

template <typename T, typename... Args>
void pointers_counter(std::ostream& ostream, const std::size_t count, T* ptr_t,
                      Args*... args) {
  ostream << "(" << count << ")" << *ptr_t;
  pointers_counter(ostream, count + 1, args...);
}

}  // namespace

template <typename T, typename... Args>
void pointers(std::ostream& ostream, T* ptr_t, Args*... args) {
  pointers_counter(ostream, 1, ptr_t, args...);
}

/*

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
NOTE!

I DIDN'T WANT TO SPEND MORE TIME FIGURING OUT HOW TO MAKE THIS WORK.
THE PROBLEM IS FOREIGN TO ME AND I DO NOT UNDERSTAND WHAT IS GOING ON WITH
COMPILER, GENERATED CODE, STRUCT WITHIN A FUNCTION, WHEN DO THE SIGNATURES
OVERLAP, HOW TO AVOID OVERLAPPING, ETC...
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

namespace hide_impl {

template <typename T, typename... Args>
void pointers(std::ostream& ostream, T* ptr_t, Args*... args) {
  // Potential TODO: Figure out how to handle this case.
  //
  // The error you're encountering stems from the fact that both versions of
  // operator() deduce to the same function signature after template
  // instantiation. This causes ambiguity during function resolution.
  //
  // To better understand why this happens, consider the scenario where you call
  // the operator() with just one argument of type T*. Both the single-argument
  // and the variadic versions of the function are potential matches, and the
  // compiler can't decide which one to pick, leading to the error.
  //
  // main.cpp:986:5: error: templates cannot be declared inside of a local class
  //   template <typename E>
  //   ^~~~~~~~~~~~~~~~~~~~~
  // main.cpp:991:5: error: templates cannot be declared inside of a local class
  //     template <typename E, typename... Rest>
  //     ^~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  struct pointers_impl {
    void operator()(std::ostream& ostream, const std::size_t order, T* ptr_t) {
      ostream << "(" << order << ")" << *ptr_t << "\n";
    }

    void operator()(std::ostream& ostream, const std::size_t order, T* ptr_t,
                    Args*... args) {
      ostream << "(" << order << ")" << *ptr_t << "\n";
      (*this)(ostream, order + 1, args...);
    }
  };

  constexpr std::size_t initial_order{1};
  pointers_impl{}(ostream, initial_order, ptr_t, args...);
}

}  // namespace hide_impl
*/

}  // namespace variadic_template

namespace sfinae_attempt {

namespace one {

// the problem
// substitution failure is not an error
// SFINAE
// if a condition is true, use this overload
// otherwise use the other overload
//

template <typename T>
struct has_size {
  // should have a member which is true or false whether type T has size
  static constexpr bool value =
      false;  // Which means that I need to retrieve value `true` or `false` at
              // compile time
              //
              // The member size can be a method or a public member and if it
              // exists no matter the type or value i should have a true here
              //
              // Is there something else that I need to know about this problem
              // to solve it?
  // the problem is that we have a type T
  // the type T at runtime can be substituted for
  // int
  // std::vector<int>
  // std::vector<string>
  // bool
  // char
  // int*
};

// which means what
// T::size
// that member is either there or it is not
// compile time checking whether T::size
// exists or not
// because it will be replaced with
// int::size
// std::vector<int>::size
// std::vector<string>::size
// int*::size
// would it even work for int*::size
//
// what is the problem there
// do we have a compile time technique to check for presence of ::size on the
// type T
//
// what of the known constructs for me can i use to solve this problem?
// ...
//
// a

template <typename T>
struct get_int {
  using type = decltype(std::declval<T>().get_int());
};

template <typename T, typename = void>
struct get_float {
  using type = void;  // Default when other one fails to substitute.
};

// welp... my head is spinning!
//
// It makes no sense to simply extract a type if the member method does not
// exist.
// The error in my thoughts is the output that I wanted by this solution. I
// realized that it does not make sense to extract a type if the member does not
// exist.
// However I might want to specify a default type if a member does not exist.
template <typename T>
struct get_float<
    T, std::enable_if_t<true, decltype(std::declval<T>().get_float())>> {
  using type = decltype(std::declval<T>().get_float());
};

void run() {
  struct rip {
    rip() = delete;  // Not constructible

    int get_int() {
      constexpr int some_int{5};
      return some_int;
    }
  };

  // The error you're seeing is because std::declval is a utility designed
  // specifically for use within the context of decltype to query the type of an
  // expression involving objects of incomplete types or non-constructed types.
  // It's not intended for use in regular executable code. In particular,
  // std::declval can't be used to actually call functions or instantiate
  // objects.
  /*
  std::cout << "Call method of non constructible type: "
            << std::declval<rip>().get_int();
   */

  std::cout << "Type of the returned type of rip::get_int(): "
            << typeid(decltype(std::declval<rip>().get_int())).name() << "\n";

  // Surprising. It doesn't work. It works within templates.
  /*
  std::cout << "Type of the returned type of rip::get_float(): "
            << typeid(decltype(std::declval<rip>().get_float())).name() << "\n";
   */

  std::cout << "Type of the rip::get_float(): "
            << typeid(get_float<rip>::type).name() << "\n";

  std::cout << typeid(int).name() << " has size: " << has_size<int>::value
            << "\n"
            << typeid(bool).name() << " has size: " << has_size<bool>::value
            << "\n"
            << typeid(std::vector<int>).name()
            << " has size: " << has_size<std::vector<int>>::value << "\n";
}

}  // namespace one

namespace two {

// Ready, Stary, Go!

}

}  // namespace sfinae_attempt

int main() {
  const auto separator{[](const std::string& label) {
    return "\n--------\n" + label + "\n--------\n\n";
  }};

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  std::cout << separator("a");

  curiously_recurring_template_pattern::a::derived derived_a;
  // Both call derived implementation.
  //
  // Derived class calls an interface method of the base
  // class which is compile time polymorphism. Which calls
  // the interface from base class which casts (this) to the
  // templated parameter to call the member method.
  //
  // derived_a.interface();
  derived_a.implementation();

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  std::cout << separator("b");

  curiously_recurring_template_pattern::b::derived derived_b;
  derived_b.interface();
  derived_b.implementation();

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  std::cout << separator("c");

  curiously_recurring_template_pattern::c::derived derived_c;
  derived_c.interface();
  derived_c.implementation();

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  std::cout << separator("d");

  curiously_recurring_template_pattern::d::derived derived_d;
  derived_d.implementation();

  // Try to determine the called method at runtime.
  curiously_recurring_template_pattern::d::base* base_ptr{&derived_d};
  base_ptr->implementation();

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  std::cout << separator("e");

  curiously_recurring_template_pattern::e::derived derived_e;
  derived_e.implementation();

  // Try to determine the called method at runtime.
  curiously_recurring_template_pattern::e::base* base_ptr_e{&derived_e};
  base_ptr_e->implementation();

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  std::cout << separator("f");

  curiously_recurring_template_pattern::f::derived_a derived_a_f;
  derived_a_f.a();

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  std::cout << separator("logger");

  // Try with and without pointers. Does it work the same?

  curiously_recurring_template_pattern::logger::info info;
  curiously_recurring_template_pattern::logger::warn warn;
  curiously_recurring_template_pattern::logger::error error;

  info.log(std::cout);
  warn.log(std::cout);
  error.log(std::cout);

  curiously_recurring_template_pattern::logger::base<
      curiously_recurring_template_pattern::logger::info>* base_ptr_info{&info};
  curiously_recurring_template_pattern::logger::base<
      curiously_recurring_template_pattern::logger::warn>* base_ptr_warn{&warn};
  curiously_recurring_template_pattern::logger::base<
      curiously_recurring_template_pattern::logger::error>* base_ptr_error{
      &error};

  base_ptr_info->log(std::cout);
  base_ptr_warn->log(std::cout);
  base_ptr_error->log(std::cout);

  // Here you're storing pointers to the base class template instantiated with
  // the derived types in base_ptr_info, base_ptr_warn, and base_ptr_error.
  // Since the log method is defined in the base class, you can call it on these
  // pointers. The CRTP ensures that the correct log_impl method is called for
  // the actual type of the object pointed to by the base pointer, due to the
  // static_cast used in the log method.
  //
  // This is an important aspect of the CRTP: it allows you to write code in the
  // base class that can work with the derived type, without needing runtime
  // polymorphism (virtual functions and a vtable). The correct function to call
  // is determined at compile time based on the template parameter, which is the
  // derived type itself.
  //
  // So yes, both approaches work, but they work because of the mechanics of the
  // CRTP, and they demonstrate the compile-time polymorphism that the CRTP
  // enables. The base class method log is able to call the log_impl method of
  // the derived class, even though it only has a pointer to the base class,
  // because of the static_cast to T*, where T is the derived class.

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  std::cout << separator("typeid");

  const std::type_info& derived_a_info{typeid(derived_a)};
  const std::type_info& derived_b_info{typeid(derived_b)};

  std::cout << "name: " << derived_a_info.name() << "\n";
  std::cout << "hash_code: " << derived_a_info.hash_code() << "\n";
  std::cout << "`derived_a_info.before(derived_b_info)`: "
            << derived_a_info.before(derived_b_info) << "\n";

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  std::cout << separator("crtp_static_method");

  curiously_recurring_template_pattern::crtp_static_method::derived
      derived_a_crtp_static_method;

  derived_a_crtp_static_method.log();
  derived_a_crtp_static_method.log_static();

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  std::cout << separator("template_parameter::run_example()");

  template_parameter::run_example();

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  std::cout << separator("sfinae");

  std::vector<int> v1{1, 2, 3, 4};
  sfinae::execute(v1, [](int n) {
    std::cout << n << " ";

    return n + 1;
  });

  std::cout << "\n";
  std::for_each(v1.begin(), v1.end(), [](int n) { std::cout << n << " "; });

  std::vector<int> v2{5, 6, 7, 8};
  std::cout << "\n";
  sfinae::execute(v2, [](int n) { std::cout << n << " "; });

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  std::cout << separator("template_parameter::f_size_t");
  sfinae::template_parameter::f_size_t<5>();
  const std::size_t four{4};
  sfinae::template_parameter::f_size_t<four>();
  sfinae::template_parameter::f_size_t<four + 1>();
  sfinae::template_parameter::f_bool<true>();
  sfinae::template_parameter::f_bool<false>();
  sfinae::template_parameter::f_type<int>();
  sfinae::template_parameter::f_type<double>();
  typedef struct {
  } stuct_type;
  sfinae::template_parameter::f_type<stuct_type>();
  struct struct_type_2 {};
  sfinae::template_parameter::f_type<struct_type_2>();

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  std::cout << separator("deduce_type::use_decltype::run()");

  deduce_type::use_decltype::run();

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  std::cout << separator("variadic_template::run()");

#ifdef __cpp_variadic_templates
  std::cout << "`__cpp_variadic_templates` is defined\n\n";
#else
  std::cout << "`__cpp_variadic_templates` is not defined\n\n";
#endif

  variadic_template::print(1, 2.0, "three");
  variadic_template::fold(1, 2.0, "three");

  {  // Scope namespace
    namespace rl = variadic_template::resource_logger;
    // Copy operations invoked?
    variadic_template::print(rl::a{}, rl::b{}, rl::c{});
    variadic_template::fold(rl::a{}, rl::b{}, rl::c{});

    variadic_template::fold_ref(rl::a{}, rl::b{}, rl::c{});
  }

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  std::cout << separator("variadic_template::run()");

  {  // Pointers...
    namespace rl = variadic_template::resource_logger;
    rl::a* ptr_a{new rl::a{}};
    rl::b* ptr_b{new rl::b{}};
    rl::c* ptr_c{new rl::c{}};

    std::cout << "\n";
    variadic_template::pointers(std::cout, ptr_a);
    std::cout << "\n";
    variadic_template::pointers(std::cout, ptr_a, ptr_b);
    std::cout << "\n";
    variadic_template::pointers(std::cout, ptr_a, ptr_b, ptr_c);
    std::cout << "\n";

    delete ptr_a;
    delete ptr_b;
    delete ptr_c;
  }

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  std::cout << separator("sfinae_attempt::one::run()");

  sfinae_attempt::one::run();

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  return 0;
}
