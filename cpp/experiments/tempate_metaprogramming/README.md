# Template metaprogramming

Attempts to perform various operations at compile time using template metaprogramming.

## Docs

Documentation how to use this directory.

### How to run

How to run in powershell:

```powershell
clang++ -std=c++17 main.cpp -o main.exe; ./main.exe
```

### How to run test

Explanation:

I used vcpkg to manually install gtest library.

```powershell
C:\src\vcpkg\vcpkg.exe install gtest --triplet x64-mingw-static
```

Then I searched for static library files in vcpkg directory:

```powershell
ls C:\src\vcpkg\installed\x64-mingw-static\
```

Where I found `manual-link` and `lib` directories containing `libgtest_main.a` and `libgtest.a`. The order of linking seems to be important. I had to link `libgtest_main.a` first and then `libgtest.a`.

This made me realize that a whole executable serves as a test. I realized that the library writers used `C++` to implement a conceptual testing environment that wraps user provided test cases. JavaScript testing framework `jest` does the same thing.

Compile and run test:

```powershell
clang++ -std=c++17 -IC:/src/vcpkg/installed/x64-mingw-static/include -LC:/src/vcpkg/installed/x64-mingw-static/lib -LC:/src/vcpkg/installed/x64-mingw-static/lib/manual-link -lgtest_main -lgtest test.cpp -lgmock_main -lgmock -o test.exe; ./test.exe
```

## Self-Notes

I tried to use struct and use recursive logic like for fibonacci to fill up a `std::array` with values.

This would be runtime equivalent to that.

```cpp
std::array<size_t, 10> result;
for(size_t i{0}; i < 10; ++i) {
  result[i] = i;
}
```

However I wanted to do it:

- Compile Time
- Recursively
- Using template and struct

The idea was to use a struct which would generate structs with static member value as index from 0 to N-1. I failed to do it and ChatGPT kept recommending me some other techniques. Like looping in constexpr function. Using constexpr function template parameters to return filled up `std::array`. I just didn't know how to think. I didn't know what to look for. I tried to set each value of `std::array` outside of the struct members.

```cpp
template<int n>
struct loop {
  static constexpr size_t value = loop<n-1>::value // ...
  std::array<size_t, n> // ...
};

// Base case specialization
```

I believe that my thinking was wrong. I came up with that idea and it was most likely incorrect idea to follow. I should have used an example and find a really similar example and figure out a way to train my mind to come up with such a solution.

I am also getting somewhat demotivated because I do not see my progress. I should measure it.

- Templates
- Templates type packing
- Templates type unpacking
- Use templates recursively
- I'm much more comfortable writing `C++` code
- Hmm... and more! I should go over all the branches with `C++` code to see what I did
  - I wrote at least 20 or 30 algorithms using `C++`
  - I wrote somewhat working code using `wxwidgets`
  - I use `CMake` build system somewhat more comfortable
  - I've read about bitwise techniques and how C++ uses bitwise options
  - I practiced `CRTP - Curiously Recurring Template Pattern`
  - I read and practiced `SFINAE - Substitution Failure is not An Error`
  - I've done variadic templates thanks to `CRTP`
  - I wrote `~1500` lines of code in `C++` thanks to exploring `CRTP`
  - I explored various C++ constructs thanks to starting `CRTP` exploration
  - I wrote `C++` and `OpenGL` code to render stuff on the screen
  - I learned about concept of framebuffer and OpenGL and how it interacts with OpenGL
  - I learned about C++ type deduction such as `decltype` and `std::declval`
  - I used C++ to build dynamic library using C++ and virtual functions
  - I made `CLI - Command Line Interface` using `boost::program_options` that connects to `Docker`
  - I learned how to think conceptually and independently of programming language
  - And much more... WoW! I should be proud of myself! I should compile lists such as this one more frequently!
