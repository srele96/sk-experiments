#include <iostream>
#include <string>
#include <typeinfo>

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

}  // namespace curiously_recurring_template_pattern

int main() {
  const auto separator{[](const std::string& label) {
    return "--------\n" + label + "\n--------\n\n";
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

  std::cout << separator("typeid");

  const std::type_info& derived_a_info{typeid(derived_a)};
  const std::type_info& derived_b_info{typeid(derived_b)};

  std::cout << "name: " << derived_a_info.name() << "\n";
  std::cout << "hash_code: " << derived_a_info.hash_code() << "\n";
  std::cout << "`derived_a_info.before(derived_b_info)`: "
            << derived_a_info.before(derived_b_info) << "\n";

  return 0;
}
