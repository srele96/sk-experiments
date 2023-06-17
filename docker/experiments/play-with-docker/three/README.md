# Three

A random idea for a service number three to use C++ and connect to postgres.

## Documentation

### Requirements

- Linux operating system
- Cmake
- Docker & Docker compose

### Setup

Run the following to obtain `libpq` required for libpqxx and linking:

```terminal
sudo apt-get install libpq-dev
```

Run the following to obtain `libpqxx` c++ client for postgresql:

```terminal
sudo apt-get install libpqxx-dev
```

The `apt-get` obtains headers and binary for the package specified.

More on:

- [How to install libpqxx](https://howtoinstall.co/en/libpqxx-dev)
- [libpqxx package info](https://packages.ubuntu.com/search?keywords=pqxx&searchon=names&suite=kinetic&section=all)
- [package search](https://packages.ubuntu.com/search?keywords=pqxx&searchon=names&suite=kinetic&section=all)
- [package files for amd64](https://packages.ubuntu.com/kinetic/amd64/libpqxx-dev/filelist).

### Build

Create build directory:

```terminal
mkdir build
```

Enter build directory:

```terminal
cd build
```

Generate build system:

```terminal
cmake ..
```

Build the project:

```terminal
cmake --build .
```

Run the executable:

```terminal
./three
```
