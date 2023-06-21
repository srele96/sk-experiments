#include <functional>
#include <iostream>
#include <queue>
#include <vector>

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

  std::priority_queue<int, std::vector<int>, std::less<int>> min_heap;

  // Fill the heap with unordered numbers
  for (int number : {3, 2, 1, 5, 10, 7}) {
    std::cout << "Push: " << number << '\n';
    min_heap.push(number);
  }

  // Print and empty the heap
  for (; !min_heap.empty(); min_heap.pop()) {
    std::cout << "Pop: " << min_heap.top() << '\n';
  }

  return 0;
}
