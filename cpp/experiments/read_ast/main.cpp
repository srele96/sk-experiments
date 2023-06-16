template <typename T>
T max(const T& first, const T& second) {
  return first > second ? first : second;
}

int main() {
  const int int_result = max(50, 15);
  const char char_result = max('a', 'b');

  return 0;
}
