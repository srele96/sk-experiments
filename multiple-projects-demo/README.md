# Multiple projects demo

This directory contains two projects:

- **project-one**
- **project-two**

Illustration of ability to have multiple projects that use their own `.gitignore`, advantage is that we can have one repository for every project.

Each directory on git may have own `README.md` which may contain whatever you want, but I like to describe what the demo is about.

## project-one and project-two

These are results of `yarn create react-app project-one` and `yarn create react-app project-two`.

Each is sufficient to prove that I can have more than one project that is not git repository.

Each of them has it's own `.gitignore` and can use it's own package manager `yarn` or `npm`.

However I don't think they can contain other projects within them, but it doesn't make sense to me and I don't want to do that.

## Motivation behind this

I've been thinking for a while how to have one repository as collection of all projects.

Having many big projects in one repository is not good idea, but since i have a lot of *small* experiments and i'd like to have one collection of everything i've done, here I am.
