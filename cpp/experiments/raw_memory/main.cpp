#include <iostream>
#include <new>

// I need a way to observe whether the allocated memory is freed when I call
// ::operator delete()
//
// And I need a way to observe whether an object that I delete using
// destination->~S() is freed
struct S {
  static int id_counter;
  int id;
  int a;
  int b;

  S(int a, int b) : a{a}, b{b}, id{next_id()} {
    std::cout << "id = " << id << " Create, S(" << a << ", " << b << ")\n";
  }

  S(const S& other) : a{other.a}, b{other.b}, id{next_id()} {
    std::cout << "id = " << id << " Copy, S(" << a << ", " << b << ")\n";
  }

  S& operator=(const S& other) {
    a = other.a;
    b = other.b;
    id = next_id();
    std::cout << "id = " << id << " Copy, S(" << a << ", " << b << ")\n";
    return *this;
  }

  S(S&& other) : a{other.a}, b{other.b}, id{next_id()} {
    std::cout << "id = " << id << " Move, S(" << a << ", " << b << ")\n";
  }

  S& operator=(S&& other) {
    a = other.a;
    b = other.b;
    id = next_id();
    std::cout << "id = " << id << " Move, S(" << a << ", " << b << ")\n";
    return *this;
  }

  ~S() {
    std::cout << "id = " << id << " Destroy, S(" << a << ", " << b << ")\n";
  }

  int next_id() { return id_counter++; }
};

int S::id_counter = 0;

int main() {
  void* memory{::operator new(sizeof(S))};

  S* s = new (memory) S{1, 2};

  std::cout << s->a << " " << s->b << "\n";

  // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  // The pattern is:
  //
  // ALlocate raw memory
  void* memory2{::operator new(sizeof(S))};

  // Construct an object
  S tmp{3, 4};
  // Create a pointer to the allocated memory and cast the memory to the type of
  // pointer
  //
  // Potential issues with alignment and something else?
  //
  // What is the guarantee that the memory stores the type of object correctly?
  S* destination{static_cast<S*>(memory2)};
  std::cout << "Before copying\n";
  *destination = tmp;
  std::cout << "After copying\n";

  std::cout << "(destination) Before modifying `tmp`: " << destination->a << " "
            << destination->b << "\n";

  tmp.a = 5;
  tmp.b = 6;

  std::cout << "(destination) After modifying `tmp`: " << destination->a << " "
            << destination->b << "\n";

  s->~S();
  // Why do I not use `delete` instead of calling destructor?
  destination->~S();
  ::operator delete(memory);
  ::operator delete(memory2);

  return 0;
}
