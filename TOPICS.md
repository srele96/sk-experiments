# List of potential topics for research

## Topics

- Create semantic and accessible website using **_ONLY_**
  - **_content from my blogs_**
  - **_HTML_**
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
- How does webpack optimize bundles?
- Git files - gitignore, gitattributes, ...
- How do callbacks in JavaScript realy work?
- JavaScript type checking - typeof, print constructor
- JavaScript performance
- HTTP caching
- Performance when working with DOM (HTML, JavaScript, CSSOM)
- HTML DOM parsing
- CSS CSSOM parsing
- How does browser parse web pages?

## Frontend cheat-sheet

### Web Knowledge

1. Caching
2. HTTP/2
3. Security

### Web Performance

1. Critical Rendering Path
2. Reflow
3. preload, pre-connect, prefetch, prerender
4. Rendering Performance
5. Workers
6. Image Optimization

### DOM

1. Elements
2. Manipulation
3. Document Fragment
4. Event delegation and bubbling

### HTML

1. Semantic Elements
2. Accessibility
3. Responsive web

### Javascript

1. this
2. Closure
3. Inheritance
4. Asynchronous Javascript
5. Hoisting
6. Currying
7. Higher-order functions

### Design patterns

1. Mixin
2. Factory
3. Singleton
4. Facade
5. MVC, MVVM
6. Server vs Client-Side Rendering

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
