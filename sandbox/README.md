# Sandbox

The Sandbox is a collection everything I want to do using C++ and everything related to the C++ ecosystem.

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
