#ifndef LAMBDA_LINEAR_ALGEBRA_COORDINATE_HPP
#define LAMBDA_LINEAR_ALGEBRA_COORDINATE_HPP

#include <functional>
#include <string>
#include <vector>

namespace linear_algebra {

struct position {
  int row;
  int column;
};

class coordinate {
 private:
  linear_algebra::position position;
  std::vector<std::function<void(const int&)>> movements;

 public:
  explicit coordinate(linear_algebra::position initial_position);
  void print_formatted_state(const std::string& message) const;
  void move_and_print_each(const std::vector<int>& vector);
};

}  // namespace linear_algebra

#endif  // LAMBDA_LINEAR_ALGEBRA_COORDINATE_HPP
