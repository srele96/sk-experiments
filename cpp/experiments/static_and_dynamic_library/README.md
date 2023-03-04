# Shared library

Guidance on how to build a library as a shared and static library, then compile a program and run it.

## Create library

Create both static and dynamic library.

```cmd
.\Library.bat
```

Clean the built libraries:

```cmd
.\Library.bat --clean
```

## Run the code that uses the library

See which flags are available:

```cmd
.\Run.bat --help
```

Run the static library:

```cmd
.\Run.bat --static
```

Run the dynamic library:

```cmd
.\Run.bat --dynamic
```

Run both
