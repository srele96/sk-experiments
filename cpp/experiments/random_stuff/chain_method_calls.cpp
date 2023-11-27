#include <iostream>

/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
/// Motivation:
///
/// I was reading Three.js code because I want to learn about computer graphics
/// concepts. I saw that they are returning `this` from class methods and
/// instantly remembered that they do it to enable chain calling of methods. The
/// immediate idea I had was that it is extremely useful to chain method calls
/// in computer graphics if we want to scale, transform, rotate, etc... Do some
/// kind of sequential or whatever operations on an object. Therefore I wanted
/// to try it out using C++.
///
/// However, immediately after writing a C++ example that enables me to chain
/// method calls by returning a reference to a struct itself, I thought that
/// there must be some space for some funny behavior. It turned out I was right!
/// Through returned reference we can mutate object, which doesn't look
/// completely right. Bjarne Stroustrup keeps saying in his talks that just
/// because we can do some things, doesn't mean that we should.
///
/// I get the feeling this was one of those. Cheers!
/// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

namespace features {

struct chainer {
  int value{50};

  const chainer& one(std::ostream& os) const {
    os << "One...";
    return *this;
  }

  const chainer& two(std::ostream& os) const {
    os << "Two...";
    return *this;
  }
};

struct bad_chainer {
  int value{25};

  bad_chainer& one(std::ostream& os) {
    os << "One...";
    return *this;
  }
  bad_chainer& two(std::ostream& os) {
    os << "Two...";
    return *this;
  }
};

}  // namespace features

int main() {
  const features::chainer chainer{};
  chainer.one(std::cout).two(std::cout);
  // The line below is commented out because it causes compiler error.
  // chainer.one(std::cout).value = 25;  // Should error...
  // I wonder do I need to use {} or is it enough to skip it? I get the hunch
  // either can work, but depends on the signature of a struct.
  features::bad_chainer bad_chainer{};
  // It is possible to retrieve values through returned reference.
  std::cout << bad_chainer.one(std::cout).two(std::cout).value;
  // Mutate bad_chainer through returned reference - weird as heck.
  // I bet linter complains about that.
  bad_chainer.one(std::cout).value = 50;
  // After mutation...
  std::cout << bad_chainer.value;
  return 0;
}
