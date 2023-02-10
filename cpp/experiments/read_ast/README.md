# Read compiler generated Abstract Syntax Tree (AST)

I saw somewhere that I could see compiler generated code. I hoped that I could see how compile replaces `inline` functions with their body. I wasn't able to do it and didn't want to spend more time. I saw that compiler generates functions using templates. I could finaly see for myself what Bjarne Stroustrup meant when he talked about usage of template metaprogramming to generate C++ code.

## How to generate

Run:

```cmd
generate.bat
```

The batch script contains code and flags to generate Abstract Syntax Tree.

## Questions for ChatGPT

### does this command produce last state of code before compilation? `clang++ -Xclang -ast-print -fsyntax-only main.cpp > out.cpp`

No, the command does not produce the final state of the code before compilation. It produces an abstract syntax tree (AST) representation of the code in main.cpp, which is a tree-like structure that represents the code's structure, elements, and relationships, but not necessarily its executable form. The AST is not valid C++ code and cannot be directly compiled or executed. It is an intermediate representation that the compiler can use to optimize and generate the final executable code.

### why is it useful to read abstract syntax tree? why does compiler generate functions from a template functions in abstract syntax tree?

The abstract syntax tree (AST) is a data structure that represents the structure of the source code. The compiler uses the AST to process the code, perform optimizations, and generate the final executable code. By reading the AST, developers can gain insight into how the compiler is processing their code and make informed decisions about how to optimize their code.

In the example you provided, the compiler generates specialized functions for int and char types from the template function based on the type of arguments passed to the function. This is a process called template instantiation, where the compiler generates specific functions for each type of argument passed to the function. The generated specialized functions are then optimized and used for actual execution, resulting in more efficient code. The AST representation of the code shows this process and how the compiler is generating these specialized functions from the template function.
