#include <iostream>

// There is more going on than meets the eye. Recursion takes time to grasp just
// like any other unfamiliar topic.
void tower_of_hanoi(const int n, const char first, const char mid,
                    const char end) {
  if (n > 0) {
    // Move n-1 from first to mid.
    tower_of_hanoi(n - 1, first, end, mid);
    // Move the remaining peg from first to end.
    std::cout << "Move from " << first << " to " << end << "\n";
    // Move n-1 from mid to end.
    tower_of_hanoi(n - 1, mid, first, end);
  }
}

int main() {
  tower_of_hanoi(3, 'A', 'B', 'C');

  return 0;
}
