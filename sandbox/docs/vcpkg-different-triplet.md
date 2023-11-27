# Vcpkg different triplet

[ChatGPT unresolved reference error conversation.](./vcpkg-different-triplet.txt)

`x64-windows` triplet configuration

```cmake
set(VCPKG_TARGET_ARCHITECTURE x64)
set(VCPKG_CRT_LINKAGE dynamic)
set(VCPKG_LIBRARY_LINKAGE dynamic)
```

`x64-mingw-dynamic` triplet configuration

```cmake
set(VCPKG_TARGET_ARCHITECTURE x64)
set(VCPKG_CRT_LINKAGE dynamic)
set(VCPKG_LIBRARY_LINKAGE dynamic)
set(VCPKG_ENV_PASSTHROUGH PATH)

set(VCPKG_CMAKE_SYSTEM_NAME MinGW)
set(VCPKG_POLICY_DLLS_WITHOUT_LIBS enabled)
```

For me, when I used `x64-mingw-dynamic` triplet, compilation worked!

It is possibly a compiler missmatch, but I didn't test whether `x64-windows` works with `msvc` compiler using visual studio.

After inspecting the `config-x64-windows-out.log` file, I found that it builds it using microsoft compiler. That makes sense why `clang` and `g++` compilers can't link against library built using windows triplet.

```txt
C:\src\vcpkg\buildtrees\gtest\config-x64-windows-out.log
```
