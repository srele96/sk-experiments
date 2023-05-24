#include <iostream>

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ FRIENDS ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// Through some obscure techniques explore what's possible using C++ friend
// functions.
// Now that I think of it, defining comparison operators as friend functions...
// Interesting.
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class Subject {
 public:
  const int whatever{10};
  friend void besto_friendo(Subject& subject) {
    std::cout << "I'm besto friendo!\n"
              << "Peaka_boo! -- " << subject.member;
  }
  using something = int;

 private:
  int member{whatever};
};

// Woah... weird. At least I find this practice obscure and confusing, but oh
// well! For the sake of experimenting!
void besto_friendo(Subject& subject);

int main() {
  constexpr Subject::something non_magic{20};
  std::cout << non_magic << '\n'; // Shut up linter!
  // Interesting... a type can be used when class acts as a namespace. An
  // integer can't be used through class name.
  // std::cout << Subject::whatever;

  Subject access_type;
  // Makes sense. I can't access the type through the object.
  // access_type::something magic{30};

  besto_friendo(access_type);
  // Obscure.

  return 0;
}
