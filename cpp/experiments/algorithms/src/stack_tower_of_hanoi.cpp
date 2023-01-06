#include <iostream>
#include <stack>
#include <string>

namespace data {

struct tower {
  char from;
  char end;
  char aux;
};

}  // namespace data

namespace algorithm {

struct function_call {
  int move;

  data::tower tower;
};

// Notes:
//
// - I am aware the algorithm is copying resources. I will learn how to handle
// that eventually, my current priority are algorithms.
//
// - The algorithm has notable difference to the recursive version. It doesn't
// behave exactly in the same way recursion does. For each last call it
// sequentially executes the three call_stack.push() calls.
//
// - Another notable difference to the recursive version is that the order of
// calls is reversed.
//
// - One more notable difference is that it requires me to explicitly do
// call_stack.push({1, { /* ... */ }}) that invokes the base case.

void tower_of_hanoi(int moves, data::tower tower) {
  std::stack<function_call> call_stack;
  call_stack.push({moves, tower});

  while (!call_stack.empty()) {
    const function_call last_call = call_stack.top();
    call_stack.pop();

    if (last_call.move == 1) {
      std::cout << "Move disk " << last_call.move << " from "
                << last_call.tower.from << " to " << last_call.tower.end
                << '\n';
    } else {
      const data::tower aux_to_end{last_call.tower.aux, last_call.tower.end,
                                   last_call.tower.from};
      call_stack.push({last_call.move - 1, aux_to_end});

      const data::tower from_to_end{last_call.tower.from, last_call.tower.end,
                                    last_call.tower.aux};
      call_stack.push({1, from_to_end});

      const data::tower from_to_aux{last_call.tower.from, last_call.tower.aux,
                                    last_call.tower.end};
      call_stack.push({last_call.move - 1, from_to_aux});
    }
  }
}

}  // namespace algorithm

namespace test {

// Notes:
//
// In the recursive solution we rely on the previous function call to hold the
// correct state. Recursive function uses First In Last Out and also terminates
// the current execution by entering itself again.
//
// The iterative solution uses a stack to hold the state of the function calls.
// It uses Last In First Out and doesn't terminate the current execution.
// Because of stack's nature, we need to reverse the order of calls. We also
// have to push the base case explicitly. Because we don't terminate execution,
// we rely on sequential calls in reverse order.

void print_recursive(int n) {
  if (n > 0) {
    print_recursive(n - 1);
    std::cout << n << " ";
    print_recursive(n - 1);
  }
}

void print_iterative(int n) {
  std::stack<int> call_stack;
  call_stack.push(n);

  while (!call_stack.empty()) {
    const int last_call = call_stack.top();
    call_stack.pop();

    if (last_call > 0) {
      call_stack.push(last_call - 1);
      std::cout << last_call << " ";
      call_stack.push(last_call - 1);
    }
  }
}

}  // namespace test

int main() {
  const int three_moves = 3;
  const data::tower tower{'A', 'C', 'B'};

  std::cout << "Moves = " << three_moves << " \n";
  algorithm::tower_of_hanoi(three_moves, tower);

  std::cout << '\n';

  const int two_moves = 2;
  std::cout << "Moves = " << two_moves << " \n";
  algorithm::tower_of_hanoi(two_moves, tower);

  std::cout << '\n';

  test::print_recursive(3);
  std::cout << '\n';
  test::print_iterative(3);

  return 0;
}
