#include <iostream>
#include <string>
#include <typeinfo>
#include <utility>

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

int main() {
  const auto separator{[](const std::string& label) {
    return "\n--------\n" + label + "\n--------\n\n";
  }};

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

  std::cout << separator("crtp_static_method - a");

  curiously_recurring_template_pattern::crtp_static_method::derived
      derived_a_crtp_static_method;

  derived_a_crtp_static_method.log();
  derived_a_crtp_static_method.log_static();

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

  std::cout << separator("template_parameter::run_example()");

  template_parameter::run_example();

  return 0;
}
