# How to run test

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
