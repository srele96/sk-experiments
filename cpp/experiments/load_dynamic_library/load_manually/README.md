# Load Manually

Build a dynamic library and write loading code manually inside the `main.cpp` file.

## Build and run

Build dynamic library:

```powershell
clang++ -fPIC -shared Library.cpp -o Library.dll
```

Compile the executable:

```powershell
clang++ -std=c++17 main.cpp -o main.exe
```

Run the executable to verify that it runs:

```powershell
./main.exe
```

## Debug if Library.dll exports symbol

- [Open Visual Studio developer command prompt](https://learn.microsoft.com/en-us/cpp/build/building-on-the-command-line?view=msvc-170#developer_command_prompt)
- [Dumpbin symbols](https://learn.microsoft.com/en-us/cpp/build/reference/symbols?view=msvc-170)

To list strings that contain "library" in the Library.dll:

```powershell
dumpbin /symbols Library.dll | findstr library
```

The output:

```powershell
C:\Users\Srecko\Documents\MyProjects\Private\container-sk-experiments\sk-experiments\cpp\experiments\load_dynamic_library\load_manually>dumpbin /symbols Library.dll | findstr library
058 00000370 SECT1  notype ()    External     | library_getint
059 00000380 SECT1  notype ()    External     | library_setint
186 00001020 SECT1  notype ()    External     | __mingw_enum_import_library_names
```
