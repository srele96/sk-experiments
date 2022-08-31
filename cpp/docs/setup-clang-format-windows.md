# Setup clang-format on Windows

1. Follow https://www.msys2.org/ tutorial to the end, it covers:
   - Install msys2
   - Install mingw64
2. Add mingw64 to system path variables
3. Verify that mingw64 works
   1. Open command prompt
   2. Run `g++ --version`
4. Verify that we don't have clang
   1. Open command prompt
   2. Run `clang++ --version`
5. Open mingw64
6. Install clang for mingw64
7. Verify that clang works
   1. Open command prompt
   2. Run `clang++ --version`
   3. Run `clang-format --version`
