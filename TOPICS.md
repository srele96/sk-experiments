# List of potential topics for research

- Prettier plugins - Format imports alphabetically and group by type
- JavaScript "asynchronous" nature - How does it really work?
- HTML script tag attributes - How does browser handle script tags?
- Currying with practical use cases
- How to create monorepo
- JavaScript how do promises use microtasks?
- NodeJS require - How does NodeJS see imported modules? What is NodeJS module?
- NodeJS express error handling
- ReactJS fetch before component is mounted
- ReactJS forms state management
- Webpack code bundling - How does webpack code output realy look like?
- How does webpack optimize bundles?
- Webpack bundle sizes
- Git files - gitignore, gitattributes, ...
- How do callbacks in JavaScript realy work?
- JavaScript type checking - typeof, print constructor
- JavaScript performance
- HTTP caching
- Performance when working with DOM (HTML, JavaScript, CSSOM)
- HTML DOM parsing
- CSS CSSOM parsing
- How does browser parse web pages?

## Additional problems

- Monorepo usage of installed npm packages

  - Package `math` with `package.json` that has content:

  ```json
  {
    "dependencies": {
      "lodash": "lodash-version-etc"
    }
  }
  ```

  - Package `cube` with `package.json` that has content:

  ```json
  {
    "dependencies": {}
  }
  ```

  - Why can package `cube` do this and it will work?

  ```js
  const lodash = require('lodash');
  ```

  - TODO:

    - Find out why does this work.
    - Does it work because it is in node modules?
    - Does it mean I need to declare installed packages in root package.json?
    - Does it mean I need to manually keep each package:
      - Dependencies
      - Peer dependencies
      - Dev dependencies
    - Clean up dependencies and remove redundant ones

      Manually up to date with root ones?

    This problem has been bugging me for a while because I'm using monorepo.

### The answers to the 'Additional problems'

Q: Why can package `cube` do require module that isn't in its `package.json`?

A: NodeJS package resolution algorithm.

---

Q: Find out why does this work.

A: The package json is configuration for the package manager and the NodeJS. NodeJS doesn't need package.json to require a package.

---

Q: Does it mean I need to declare installed packages in root package.json?

A: The package JSON should be shipped when publishing packages. The package JSON tells the users what npm needs to install to allow our package to work.

---

Q: Does it mean I need to manually keep each package:

- Dependencies
- Peer dependencies
- Dev dependencies

A: We can manually modify package names and versions in the package JSON. Each dependency type has a use case. The package developer should decide what dependency type he needs.

## Develop APIs on RapidAPI

Do it.

## More about this list

In this file can be found list of topics I am interested in.

This list may and will change, some topics will just get removed.

This file is most likely going to have more topics that I can ever cover, some may be delayed.

As I get new interesting ideas, they will be added here.
