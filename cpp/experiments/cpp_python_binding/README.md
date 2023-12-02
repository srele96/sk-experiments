# C++ Python binding

A C++ to Python binding sample that does whatever the f\*ck it wants.

# WARNING! USING PYTHON VIRTUAL ENVIRONMENT WILL MAKE CMAKE FIND THE PYTHON FROM THE VIRTUAL ENVIRONMENT. WHICH MIGHT RESULT IN BUILT LIBRARY `.PYD` REQUIRE INCORRECT PYTHON DLL.

# Absolutely make sure you have only one python on your system otherwise there might be a problem.

## Run

```powershell
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=C:\src\vcpkg\scripts\buildsystems\vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-mingw-static
```

```powershell
cmake --build build
```

```powershell
python something.py
```
