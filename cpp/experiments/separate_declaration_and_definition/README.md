# Separate Declaration and Definition

I didn't **see** before, but it seems i can separate definition and declaration in the same file.

## What does it mean?

In C++ we separate code to header and source files. Header files are like signing up for school. I can see the list of subjects I will have in the next year or during whole school course, but I don't know what will be the content of each subject. Source files are like going to school. I am participating in lectures, as if I was reading the content of source file.

Include replacement is important when using header-only code. There will be no source files, preprocessor will replace include with the content of header file.

What happens if header has **WHAT** and source has **HOW**? Since preprocessor replaces include with declaration, it should still work.
