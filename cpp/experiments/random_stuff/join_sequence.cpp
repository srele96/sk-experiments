#include <iostream>
#include <numeric>
#include <string>
#include <vector>

int main() {
  std::cout << "Verifying that program runs!\n";

  std::vector<std::string> v{"hello", "world", "how", "are", "you"};
  // Get used to how std::accumulate works
  std::string accumulated{
      v.size() > 0
          // See StackOverflow answer:
          // https://stackoverflow.com/questions/5689003/how-to-implode-a-vector-of-strings-into-a-string-the-elegant-way
          //
          // See why std::next. ++v.begin() won't always compile.
          // https://en.cppreference.com/w/cpp/iterator/next
          ? std::accumulate(std::next(v.begin()), v.end(), *v.begin(),
                            [](const std::string& a, const std::string& b) {
                              // See what does std::accumulate pass to a and b.
                              std::cout << "a: " << a << ", b: " << b << "\n";
                              return a + "->" + b;
                            })
          : ""};
  std::cout << "Accumulated: " << accumulated << "\n"
            << std::string{} << "\n"          // Instead of literal.
            << std::string{"Hello"} << "\n";  // Instead of literal.

  return 0;
}
