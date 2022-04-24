# Scaffolding Node Modules, NodeJS

Cool facts about node modules directory.

- Can be created manually.
- Is looked up by NodeJS when requiring module.
- Imports can be configured through `package.json`.
- Is subject to [NodeJS module resolution algorithm](https://nodejs.org/api/modules.html#all-together)
- Manual creation can be used to see how resolution or package.json configuration works.

_Note: It is difficult to experiment in large projects. If node modules have a lot of libraries, there is no guarantee that some may affect our imports._

## Proof of Concept

Repository: [Scaffolding node modules](https://github.com/srele96/scaffolding-node-modules)

In this repository, I have manually created node_modules directory.

Added packages inside it and required them from script, then ran the script with NodeJS.
