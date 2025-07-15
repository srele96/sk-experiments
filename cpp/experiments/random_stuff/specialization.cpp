template <int N, typename T>
struct __contain : public __contain<N - 1, T> {
  T value;

  template <int Idx>
  void set(T v) {
    if constexpr (Idx == N) {
      value = v;
    } else {
      __contain<N - 1, T>::template set<Idx>(v);
    }
  }

  template <int Idx>
  T get() const {
    if constexpr (Idx == N) {
      return value;
    } else {
      return __contain<N - 1, T>::template get<Idx>();
    }
  }
};

template <typename T>
struct __contain<0, T> {};

int main() {
  __contain<4, float> contain;
  contain.set<2>(3.14);
  contain.set<3>(2.71);
  contain.get<2>();
  contain.get<3>();

  return 0;
}
