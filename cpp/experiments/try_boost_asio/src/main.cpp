#include <algorithm>
// TODO(include error): Find a way to remove include errors.
#include <boost/lambda/lambda.hpp>
#include <iostream>
#include <iterator>

int main() {
  using namespace boost::lambda;
  typedef std::istream_iterator<int> in;

  std::for_each(in(std::cin), in(), std::cout << (_1 * 3) << " ");
}
