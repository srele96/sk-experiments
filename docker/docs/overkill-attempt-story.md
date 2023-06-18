# Overkill attempt story

Due to lack of understanding of how to use library in C++ I tried to build the postgres c++ client. First I was on windows, realized Docker uses linux and host is on Windows. Then I swapped to Linux and tried to build the library. After trying to build library I realized it would be a problem to build it inside docker image. I realized that I could use `apt-get` to setup library on the host and inside the docker image. Gosh...

The documentation below is the result of my attempts to build the library. I realized it is overly complex for my use case and that `apt-get` does the job.

## Requirements

Linux operating system.

## Documentation

```terminal
git clone --depth 1 --branch REL_15_3 https://github.com/postgres/postgres.git
```

```terminal
cd postgres
```

[Installation procedure for postgres 15](https://www.postgresql.org/docs/15/install-procedure.html)

```terminal
./configure
```

If you see an error [configure: error: readline library not found](https://askubuntu.com/questions/89389/how-to-solve-configure-error-readline-library-not-found).

If you see an error[configure: error: zlib library not found](https://askubuntu.com/questions/1169754/configure-error-could-not-find-the-zlib-library)

The  `./configure` command should complete successfully by now.

```terminal
make all
```

### OPTIONAL! If you get error `bison` is missing

```terminal
ERROR: `bison' is missing on your system. It is needed to create the
file `gram.c'. You can either get bison from a GNU mirror site
or download an official distribution of PostgreSQL, which contains
pre-packaged bison output.
```

Run to check `bison` names:

```terminal
apt-cache search bison
```

```terminal
sudo apt-get install bison
```

Verify that `bison` is installed:

```terminal
which bison
```

Answer [here](https://stackoverflow.com/questions/3827938/ubuntu-how-to-install-flex-to-make-postgres) tells that I should run `./configure` again to make it aware of `bison`. The answer mentions `flex` but I believe it should work for `bison` too.

```terminal
./configure
```

```terminal
make all
```

### OPTIONAL! If you get error `flex` is missing

```terminal
ERROR: `flex' is missing on your system. It is needed to create the
file `bootscanner.c'. You can either get flex from a GNU mirror site
or download an official distribution of PostgreSQL, which contains
pre-packaged flex output.
```

Run to check `flex` names:

```terminal
apt-cache search flex
```

```terminal
sudo apt-get install flex
```

Verify that `flex` is installed:

```terminal
which flex
```

Answer [here](https://stackoverflow.com/questions/3827938/ubuntu-how-to-install-flex-to-make-postgres) works for `bison` and `flex`. I should run `./configure` again to make it aware of both `flex` and `bison`.

```terminal
./configure
```

```terminal
make all
```

### Build `libpqxx`

```terminal
git clone --depth 1 --branch  7.7.5 https://github.com/jtv/libpqxx.git
```

```terminal
cd libpqxx
```

The library is built inside `/usr/local/pgsql` directory.
