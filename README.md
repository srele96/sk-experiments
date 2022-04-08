# Collection of research

This repository is collection of topics I have researched because I found them interesting.

## Migration to monorepo

Migration to monorepo allowed me to share one configuration for every project in `yes-module` directory.

Another advantage is having one node_modules in the root so I don't have to navigate around to run `npm install`.

Another breaking change is migration to yarn 3 because it provides improved support for workspaces.

## Motivation for this repository

Three years ago I started working on habit to continuously learn. Over the time amount of time spent learning increased, amount of personal projects grew proportionally. Before decision to create this repository, I realized I had a lot of work locally, disorganized.

I decided to start one repository and stash all the work. Here I publish work and ideas regularly.

This repository started small, grew untill it had a couple of projects and each of them had node_modules or some weird setup. Afterwards I learned about concept of monorepos and after some time I learned how to do it.

Since creation of this repository, majority of my work is located here.

## Navigation instructions

There are three important directories:

- archive
- no-module
- yes-module

### Archive

This directory contains archived work which I can look back on and reflect on how much I have improved.

### no-module

This directory contains work that doesn't require node_modules, it doesn't make sense to make it a workspace.

### yes-module

Here are workspaces, these projects require work with package manager, node_modules or configuration.

## TODO

- ~~- Turn this repo to [monorepo](https://dev.to/alexeagleson/how-to-create-a-node-and-react-monorepo-with-git-submodules-2g83)~~ DONE
