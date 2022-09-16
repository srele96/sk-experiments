# Create repository tree

Create a repository tree that excludes files from .gitignore and writes it to a text file.

## View the file

You can view the tree in the file [tree.txt](./tree.txt).

## Full command

Print the whole file tree to the file `tree.txt`.

```terminal
git ls-tree -r --name-only HEAD | tree --fromfile > tree.txt
```

## Print files in the current directory

The command `git ls-tree` helps us get file paths, it is very useful because I am already using git for version control.

The following command will print files in the current directory:

```terminal
git ls-tree HEAD
```

This is the output:

```terminal
srecko@srecko-desktop:~/Documents/projects/container-sk-experiments/sk-experiments$ git ls-tree HEAD
100644 blob 07552cfff88bafaf4d207e6255394bc6d6215302	.editorconfig
040000 tree bad91e112a0ec73aa3b983a3ca20cd94df6022fc	.github
100644 blob 561dcd4d53a28d29bed47a41d945b09aa8b447c6	README.md
100644 blob e196c78b80aa4a46b3c832988be1a1f76bd4f81c	TOPICS.md
040000 tree 5de623e09c800d71f26d5fa69f4e028f0f96c799	cpp
040000 tree b30c81fa09675959920765d2dbe9456c6132949f	javascript
040000 tree 65c143f6a3269c62e357ca6a9f99ec09920d843c	python
srecko@srecko-desktop:~/Documents/projects/container-sk-experiments/sk-experiments$
```

## Print files in the current and every subdirectory

The command `git ls-tree -r` will print files in the current and every subdirectory.

```terminal
git ls-tree -r HEAD
```

This is the output:

```terminal
srecko@srecko-desktop:~/Documents/projects/container-sk-experiments/sk-experiments$ git ls-tree -r HEAD
100644 blob 07552cfff88bafaf4d207e6255394bc6d6215302	.editorconfig
100644 blob 9a3b079d9b8bb678e4a0d8429a09fe37ca629be2	.github/ISSUE_TEMPLATE/issue-questionnaire.md
100644 blob e7fbde68ced801b569989e26296cf2b9902dbdfd	.github/commit-convention.md
100644 blob 59af7d4134038459d413cf747bceeea28ed280bc	.github/workflows/format.yml
100644 blob 561dcd4d53a28d29bed47a41d945b09aa8b447c6	README.md
100644 blob e196c78b80aa4a46b3c832988be1a1f76bd4f81c	TOPICS.md
100644 blob ae7e007753d68e36f70e0f9d5ea4c696fe1860c8	cpp/.clang-format
100644 blob 6d44e4f3e4e7e665cd2c6ef7c88924deca7d6a31	cpp/.clang-tidy
100644 blob b883f1fdc6d69146f477bba77c117fbbd33714af	cpp/.gitignore
100644 blob dde3146ee4a9a27cd8aee1453f68463d4b84d2f5	cpp/README.md
100644 blob 389114b7804285571ea633c17ecaeec896a29759	cpp/docs/README.md
100644 blob 39cfd4484014af7870bc329bb481b89b70ad4d26	cpp/docs/important-concepts.md
```

## Print only file names of the current and every subdirectory

The command `git ls-tree -r --name-only` will print only file names in the current and every subdirectory.

```terminal
git ls-tree -r --name-only HEAD
```

This is the output:

```terminal
srecko@srecko-desktop:~/Documents/projects/container-sk-experiments/sk-experiments$ git ls-tree -r --name-only HEAD
.editorconfig
.github/ISSUE_TEMPLATE/issue-questionnaire.md
.github/commit-convention.md
.github/workflows/format.yml
README.md
TOPICS.md
cpp/.clang-format
cpp/.clang-tidy
cpp/.gitignore
cpp/README.md
cpp/docs/README.md
cpp/docs/important-concepts.md
cpp/docs/setup-clang-format-windows.md
cpp/experiments/README.md
```

## Print file tree

That is great, now all that we need is to use the tree command on Linux.

```terminal
tree
```

This is the output of the tree command:

```terminal
srecko@srecko-desktop:~/Documents/projects/container-sk-experiments/sk-experiments$ tree
.
├── cpp
│   ├── docs
│   │   ├── important-concepts.md
│   │   ├── README.md
│   │   └── setup-clang-format-windows.md
│   ├── experiments
│   │   ├── build-static-library
│   │   │   ├── main.cpp
│   │   │   ├── Point.cpp
│   │   │   ├── Point.hpp
│   │   │   └── README.md
│   │   ├── build-with-cmake
│   │   │   ├── CMakeLists.txt
│   │   │   ├── README.md
│   │   │   └── source
│   │   │       ├── CMakeLists.txt
│   │   │       ├── main.cpp
│   │   │       ├── Point.cpp
│   │   │       └── Point.hpp
│   │   ├── README.md
│   │   ├── runner
│   │   │   ├── main.cpp
│   │   │   ├── README.md
│   │   │   └── run.bat
│   │   └── sum_combinations_of_four
│   │       ├── main.cpp
│   │       ├── README.md
│   │       └── run.bat
│   └── README.md
```

You may think this is fine, but `tree` is going to print everything. What about files ignored by our version control? That is why we have to use git ls-tree.

## Combine the commands

So now that we have both tools, I have to get a tree to print file names from git ls-tree, and there is the right tool for it.

The command `tree --fromfile` is going to read the output of the previous command, and we come to the final command.

```terminal
git ls-tree -r --name-only HEAD | tree --fromfile
```

We can read this command as follows:

Print file names of the current directory and every subdirectory recursively then read those file names and form the tree.

When we say <first_command> | <second_command>, we can read it as:

Execute the first command, then insert the output of the first command to the input of the second command and insert the output of the second command to our screen.

The last thing we have to do is to write it to a text file, and the simplest form is like this:

```terminal
echo "some content" > file.txt
```

That means we will "echo" something to the file since we have everything that we need, the final thing goes like this:

```terminal
git ls-tree -r --name-only HEAD | tree --fromfile > tree.txt
```
