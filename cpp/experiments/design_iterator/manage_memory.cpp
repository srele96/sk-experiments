#include <iostream>
#include <vector>

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// This file helps me think about memory management.
//
// The problem:
// The function void use(const params& _params) takes a struct with three
// values of the same type. Those three values are taken by const reference.
// However, below that we store each list inside a struct. To store it inside
// a struct, it has to create a copy of it. I was thinking about the struct
// storing a constant reference to the data. However, later code (that's not
// here) was calling move constructor for the struct that stored const
// reference. I wasn't sure how to handle that case... I did not mutate data
// inside the struct, but it still created a copy! I am quite sure that's the
// wrong way to handle that, i shouldn't copy that if i won't mutate it. However
// even after playing around with this example, I didn't figure it out. However,
// I still played with LLDB and I got to see how **COMPILER** actually decides
// whether it should call copy or move constructor, destructor, etc...
//
// I already knew that, but it is a totally different thing once I see it with
// my own eyes! I could move through the code and see what happens inside
// constructors, destructors, copy and move assignments, awesome! C++ feels
// really powerful, I love the amount of features it provides!
//
// Those are my findings from using the code in this file...
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class my_data {
 private:
  int m_key;

 public:
  explicit my_data(int key) : m_key{key} { std::cout << m_key << " ctor\n"; }
  my_data(const my_data& other) : m_key{other.m_key} {
    std::cout << m_key << " copy ctor\n";
  }
  my_data(my_data&& other) noexcept : m_key{other.m_key} {
    std::cout << m_key << " move ctor\n";
  }
  my_data& operator=(const my_data& other) {
    if (this != &other) {
      m_key = other.m_key;
      std::cout << m_key << " copy assignment\n";
    }
    return *this;
  }
  my_data& operator=(my_data&& other) noexcept {
    m_key = other.m_key;
    std::cout << m_key << "move assignment\n";
    return *this;
  }
  ~my_data() { std::cout << m_key << " dtor\n"; }
};

struct params {
  my_data one;
  my_data two;
  my_data three;
};

struct data {
  const my_data one;
  const int accessor;
};

void use(const params& _params) {
  const int accessor_one = 1;
  const int accessor_two = 2;
  const int accessor_three = 3;

  std::vector<data> list{
      {_params.one, accessor_one},
      {_params.two, accessor_two},
      {_params.three, accessor_three},
  };
}

int main() {
  const int key_one{1};
  const int key_two{2};
  const int key_three{3};

  const my_data one{key_one};
  const my_data two{key_two};
  const my_data three{key_three};

  const params _params{one, two, three};

  use(_params);

  return 0;
}
