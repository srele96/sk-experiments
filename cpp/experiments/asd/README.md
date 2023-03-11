# asd

## Setup dependencies

Requirements:

- `clang` - C compiler.
- `llvm-ar` - Tool to create static library, check `BuildMongooseLib` scripts.

1. Create directory `dependencies\mongoose`
2. Create `dependencies\mongoose\mongoose.c` and `dependencies\mongoose\mongoose.h
3. Download [`mongoose.c`](https://github.com/cesanta/mongoose/blob/7.9/mongoose.c) to `dependencies\mongoose\mongoose.c`
4. Download [`mongoose.h`](https://github.com/cesanta/mongoose/blob/7.9/mongoose.h) to `dependencies\mongoose\mongoose.h`
5. Run `.\BuildMongooseLib`
