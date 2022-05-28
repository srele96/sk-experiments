# Babel transpilation - React, TypeScript, ES5

Example in `index.js` shows how babel transpiles code with help of presets.

Presets used:

- @babel/preset-env
- @babel/preset-typescript
- @babel/preset-react

Below are provided examples of written and transpiled code, by each of these plugins.

## @babel/preset-env

This preset allows usage of latest JavaScript syntax, code is transpiled for older browsers to understand it.

Below are examples of written and transpiled code.

Written code:

```js
const person = {
  name: 'John',
  lastName: 'Doe',
};

const { name } = person;
```

Without `@babel/preset-env` is transpiled to:

```js
const person = {
  name: 'John',
  lastName: 'Doe',
};
const { name } = person;
```

The code didn't get transpiled, this is because preset wasn't used.

However, if this preset is used, the output is as follows:

```js
'use strict';

var person = {
  name: 'John',
  lastName: 'Doe',
};
var name = person.name;
```

## @babel/preset-typescript

This preset adds support for TypeScript.

Below are examples of written and transpiled code.

Written code:

```ts
interface Person {
  name: string;
  lastName: string;
}

const person: Person = {
  name: 'John',
  lastName: 'Doe',
};
```

Transpiled code:

```js
'use strict';

var person = {
  name: 'John',
  lastName: 'Doe',
};
```

## @babel/preset-react

Inside the browser we can include react cdn builds. This is done through html script tags.

Example of adding and using react through cdn:

```html
<!DOCTYPE html>
<html lang="en">
  <head>
    <title>React app</title>
  </head>
  <body>
    <div id="root"></div>

    <script
      crossorigin
      src="https://unpkg.com/react@17/umd/react.development.js"
    ></script>
    <script
      crossorigin
      src="https://unpkg.com/react-dom@17/umd/react-dom.development.js"
    ></script>

    <script>
      function App() {
        return React.createElement('h1', null, 'React app');
      }

      var root = document.getElementById('root');
      ReactDOM.render(React.createElement(App), root);
    </script>
  </body>
</html>
```

If you worked with `create-react-app` code below is familiar.

```jsx
function App() {
  return <div>Hello World</div>;
}
```

However, this preset transpiles it to following:

```js
'use strict';

function App() {
  return /*#__PURE__*/ React.createElement('div', null, 'Hello World');
}
```

Transpiled code looks familiar like one in cdn example. This is because react-jsx is transpiled to code understandable by browser.
