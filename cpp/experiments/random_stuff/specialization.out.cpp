///////////////////////////////////////////////////////////////////////////////
// This file is the output of the following command:
//
// clang-format off
///////////////////////////////////////////////////////////////////////////////
// clang++ -std=c++17 specialization.cpp -Xclang -ast-print -fsyntax-only > specialization.out.cpp
///////////////////////////////////////////////////////////////////////////////
// clang-format on
///////////////////////////////////////////////////////////////////////////////

template <int N, typename T>
struct __contain : public __contain<N - 1, T> {
  T value;

  template <int Idx>
  void set(T v) {
    if (Idx == N) {
      this->value = v;
    } else {
      __contain<N - 1, T>::template set<Idx>(v);
    }
  }

  template <int Idx>
  T get() const {
    if (Idx == N) {
      return this->value;
    } else {
      return __contain<N - 1, T>::template get<Idx>();
    }
  }
};

template <>
struct __contain<4, float> : public __contain<4 - 1, float> {
  float value;

  template <int Idx>
  void set(float v);

  template <>
  void set<2>(float v) {
    if (2 == 4)
      ;
    else {
      this->__contain<4 - 1, float>::template set<2>(v);
    }
  };

  template <>
  void set<3>(float v) {
    if (3 == 4)
      ;
    else {
      this->__contain<4 - 1, float>::template set<3>(v);
    }
  };

  template <int Idx>
  float get() const;

  template <>
  float get<2>() const {
    if (2 == 4)
      ;
    else {
      return this->__contain<4 - 1, float>::template get<2>();
    }
  };

  template <>
  float get<3>() const {
    if (3 == 4)
      ;
    else {
      return this->__contain<4 - 1, float>::template get<3>();
    }
  };
};

template <>
struct __contain<3, float> : public __contain<3 - 1, float> {
  float value;

  template <int Idx>
  void set(float v);

  template <>
  void set<2>(float v) {
    if (2 == 3)
      ;
    else {
      this->__contain<3 - 1, float>::template set<2>(v);
    }
  };

  template <>
  void set<3>(float v) {
    if (3 == 3) {
      this->value = v;
    }
  };

  template <int Idx>
  float get() const;

  template <>
  float get<2>() const {
    if (2 == 3)
      ;
    else {
      return this->__contain<3 - 1, float>::template get<2>();
    }
  };

  template <>
  float get<3>() const {
    if (3 == 3) {
      return this->value;
    }
  };
};

template <>
struct __contain<2, float> : public __contain<2 - 1, float> {
  float value;

  template <int Idx>
  void set(float v);

  template <>
  void set<2>(float v) {
    if (2 == 2) {
      this->value = v;
    }
  };

  template <int Idx>
  float get() const;

  template <>
  float get<2>() const {
    if (2 == 2) {
      return this->value;
    }
  };
};

template <>
struct __contain<1, float> : public __contain<1 - 1, float> {
  float value;
  template <int Idx>
  void set(float v);
  template <int Idx>
  float get() const;
};

template <>
struct __contain<0, float> {};

template <typename T>
struct __contain<0, T> {};

int main() {
  __contain<4, float> contain;
  contain.set<2>(3.1400000000000001);
  contain.set<3>(2.71);
  contain.get<2>();
  contain.get<3>();
  return 0;
}
