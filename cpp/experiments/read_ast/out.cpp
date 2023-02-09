// I inserted spaces and formatted the file to make it easier to read.
// I commited file to Version Control System to be able to read it when visiting
// repository.

template <typename T>
T max(const T &first, const T &second) {
  return first > second ? first : second;
}

template <>
int max<int>(const int &first, const int &second) {
  return first > second ? first : second;
}

template <>
char max<char>(const char &first, const char &second) {
  return first > second ? first : second;
}

int main() {
  const int int_result = max(50, 15);
  const char char_result = max('a', 'b');

  return 0;
}
