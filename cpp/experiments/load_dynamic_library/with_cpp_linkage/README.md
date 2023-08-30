# With C++ linkage

Try out an example my friend showed me.

## Compile and run

Compile the library to shared library:

```powershell
clang++ -fPIC -shared Library/Library.cpp -o Library.dll
```

Compile the executable to use the library:

```powershell
clang++ -std=c++17 main.cpp -o main.exe -L./ -lLibrary
```

Run the executable:

```powershell
./main.exe
```

## Dumpbin

The executable still contained symbols from the library.

```txt
C:\Users\Srecko\Documents\MyProjects\Private\container-sk-experiments\sk-experiments\cpp\experiments\load_dynamic_library\with_cpp_linkage>dumpbin /exports Library.dll
Microsoft (R) COFF/PE Dumper Version 14.36.32532.0
Copyright (C) Microsoft Corporation.  All rights reserved.


Dump of file Library.dll

File Type: DLL

  Section contains the following exports for Library.dll

    00000000 characteristics
    64EFB325 time date stamp Wed Aug 30 23:22:45 2023
        0.00 version
           1 ordinal base
           1 number of functions
           1 number of names

    ordinal hint RVA      name

          1    0 00001370 _Z11library_addii

  Summary

        1000 .CRT
        1000 .bss
        1000 .data
        2000 .debug_abbrev
        1000 .debug_aranges
        1000 .debug_frame
        7000 .debug_info
        2000 .debug_line
        2000 .debug_line_str
        2000 .debug_loclists
        1000 .debug_rnglists
        1000 .debug_str
        1000 .edata
        1000 .idata
        1000 .pdata
        1000 .rdata
        1000 .reloc
        2000 .text
        1000 .tls
        1000 .xdata
```

Without definining `__declspec(dllexport)` the command `dumpbin /exports Library.dll` doesn't show the `int Library::Add(int, int)` in exported symbols.

### How to use dumpbin

The dumpbin utility is a Windows-specific tool used for examining the contents of PE (Portable Executable) format files, such as .exe, .dll, and .obj files. It can display various kinds of information, such as headers, symbols, dependencies, and more. Here are some ways you can analyze a binary using dumpbin:
Examining Symbols

`dumpbin /symbols` gives you a list of symbols within a binary. Symbols can include function names, global variables, and more. This can be helpful for debugging or reverse engineering.

```cmd
dumpbin /symbols my_file.exe
```

Viewing Dependencies

`dumpbin /dependents` shows you the list of DLLs that a particular executable or DLL depends on.

```cmd
dumpbin /dependents my_file.exe
```

File Headers

`dumpbin /headers` provides you with details about the PE headers and sections in the binary.

```cmd
dumpbin /headers my_file.exe
```

Exports and Imports

`dumpbin /exports`: Lists the functions that a DLL exports.

```cmd
dumpbin /exports my_file.dll
```

`dumpbin /imports`: Lists the functions that a binary imports from other DLLs.

```cmd
dumpbin /imports my_file.exe
```

Disassembly

`dumpbin /disasm` provides disassembled code, which is useful for low-level analysis.

```cmd
dumpbin /disasm my_file.exe
```

Summary

`dumpbin /summary` gives you a brief overview of the various headers and sections in the binary.

```cmd
dumpbin /summary my_file.exe
```

By using these `dumpbin` options, you can obtain a thorough analysis of your binary files, helping you debug issues, understand dependencies, or even perform reverse engineering tasks.
