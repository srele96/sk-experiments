#include <iostream>
#include <queue>

int main() {
  std::priority_queue<int> max_heap;

  // Fill the heap with unordered numbers
  for (int number : {3, 2, 1, 5, 10, 7}) {
    std::cout << "Push: " << number << '\n';
    max_heap.push(number);
  }

  // Print and empty the heap
  for (; !max_heap.empty(); max_heap.pop()) {
    std::cout << "Pop: " << max_heap.top() << '\n';
  }

  return 0;
}
