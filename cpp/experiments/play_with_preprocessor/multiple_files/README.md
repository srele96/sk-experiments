# Run C++ preprocessor on multiple files

Running preprocessor on multiple files outputs bunch of text together to standard output stream. This isn't useful because I wanted to see how does C++ compiler compile each `CPP` separately.

However it does make sense to compile each C++ file separately. Replace content of includes which may be a declaration if header contains only declaration. That declaration prevents errors because the compiler knows its declared somewhere. At linking stage, linker is responsible to find object files which contain definition of that declaration. I guess that's what unresolved reference or symbol means.

Run:

```cmd
preprocess.bat
```
