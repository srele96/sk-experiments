# Three

A random idea for a service number three to use C++ and connect to postgres.

Versions are all messed up... For example, I just realized that `apt-get` may not have the latest version of the package. One option is to build the version I need by myself and setup the build steps for docker container as well. Another is to just use `apt-get` and say whatever... It won't work later because it currently downloads the latest version. That doesn't matter because I won't need to run this sample later, anyway, well hopefully.

## Documentation

### Requirements

- Linux operating system
- Cmake
- Docker & Docker compose

### Setup

Run the following to obtain `libpq-dev` required for libpqxx and linking:

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
- [package files for amd64](https://packages.ubuntu.com/kinetic/amd64/libpqxx-dev/filelist)

### Build

Download includes because I don't like to commit code that I didn't write especially when it's thousands of lines long because then my GitHub repository increases the % of code in that language that I didn't write.

Make the script executable to download include:

```terminal
chmod +x ./download_include.sh
```

Download include:

```terminal
./download_include.sh
```

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
cmake -DCMAKE_CXX_STANDARD=17 -DCMAKE_CXX_COMPILER=clang++ ..
```

Build the project:

```terminal
cmake --build .
```

Run the executable:

```terminal
./three
```
