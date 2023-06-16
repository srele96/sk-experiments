#include <iostream>

namespace linear_combinations {

struct coordinate {
  int x;
  int y;
};

class vector {
 public:
  explicit vector(linear_combinations::coordinate coordinate)
      : coordinate_{coordinate} {}

  friend vector operator+(vector lhs, const vector& rhs) {
    lhs.coordinate_.x += rhs.coordinate_.x;
    lhs.coordinate_.y += rhs.coordinate_.y;

    return lhs;
  }

  void multiply(const int& scalar) {
    coordinate_.x *= scalar;
    coordinate_.y *= scalar;
  }

  linear_combinations::coordinate coordinate_;
};

};  // namespace linear_combinations

namespace driver {

struct operand {
  int scalar;
  linear_combinations::vector vector;
};

struct operands {
  operand a;
  operand b;
  linear_combinations::vector result;
};

void print_operation(const operands& operands) {
  // scalar * [u1, u2] + scalar * [w1, w2] = [r1, r2]
  std::cout << operands.a.scalar << " * [" << operands.a.vector.coordinate_.x
            << ", " << operands.a.vector.coordinate_.y << "]";

  std::cout << " + ";

  std::cout << operands.b.scalar << " * [" << operands.b.vector.coordinate_.x
            << ", " << operands.b.vector.coordinate_.y << "]";

  std::cout << " = ";

  std::cout << "[" << operands.result.coordinate_.x << ", "
            << operands.result.coordinate_.y << "]";

  std::cout << "\n";
}

struct two_vectors {
  linear_combinations::vector u;
  linear_combinations::vector w;
};

void print_linear_combinations(const two_vectors& vectors, const int& amount) {
  for (int i = 0; i != amount; ++i) {
    for (int j = 0; j != amount; ++j) {
      linear_combinations::vector vec_u = vectors.u;
      vec_u.multiply(i);

      linear_combinations::vector vec_w = vectors.w;
      vec_w.multiply(j);

      linear_combinations::vector result = vec_u + vec_w;

      const operand first{i, vec_u};
      const operand second{j, vec_w};
      const operands add{first, second, result};

      print_operation(add);
    }
  }
}

};  // namespace driver

int main() {
  const linear_combinations::coordinate right_up{1, 1};
  linear_combinations::vector vector_u{right_up};
  const linear_combinations::coordinate right_down{1, -1};
  linear_combinations::vector vector_w{right_down};

  const driver::two_vectors vectors{vector_u, vector_w};

  const int each_scalar_goes_to_five = 5;
  driver::print_linear_combinations(vectors, each_scalar_goes_to_five);

  return 0;
}
