# Sandbox

The Sandbox is a collection of module and sample units which allow me to do everything I want using C++ and its ecosystem.

## Building `sandbox` samples and modules

Make sure you have [CMake](https://cmake.org/). _(I am sorry. I forgot what it's like to setup CMake when I did it for the first time and some steps are definitely missing. I will update documentation if a new unfamiliar person encounters issues. Contact me and I will help!.)_

1. Make sure you are in `sk-experiments/sandbox` directory.
2. Make `build` directory `mkdir build`
3. Generate project `cmake ..`
4. Build project: `cmake --build .`

Running the samples: _(If you managed to build, you should be able to run them. I didn't decide yet on how to manage this part, so I left it as it is. It is somewhat inconvenient because the path is long-ish, but oh well...)_

See the paths to executables and run them.

## Note

**The reason for _Sandbox_ to be right below the root directory is to allow _SANDBOXING (pun intended)_ of the sandbox directory. Everything in related to `CI/CD` for _Sandbox_ should try to isolate itself from the other parts of _sk-experiments_. The same goes for anything else related to _Sandbox_ that's outside of it.**

## Goals

I want to Evolve and avoid following any binding restrictions. Some of the goals:

- Reusability of declared dependencies
- Individual binary for each sample that can compile and run individually
- Reusability of modules that I want to reuse

Advantages of the Sandbox concept:

- Each sample may use shared dependencies across the whole sandbox. That reduces the overhead of declaring and setting up same dependency multiple times for different samples or modules.
- Independent samples which allow me to play to my heart's content with libraries and building my own. Pros of samples are that they don't care about restrictions and they behave as a fresh new project with benefit of reusing existing dependencies or my modules.
- Reusability of my own modules that I want to use in other projects that I create.
- Dedicated C++ sandbox for unbounding fun with the related ecoystem.

## Description

I like having a project where I can do a bunch of experiments/projects together and not being limited by what I can or can not do. I like to use different libraries, frameworks, etc... Therefore I could simply use CMake to initialize a project using C++ and I could set it up however I wish! Probably could follow the same organization from `sk-experiments`.
