const { createElement: e, useEffect } = require('react');

function App() {
  useEffect(() => {
    console.log('It runs!');
  });

  return e('h1', null, 'App');
}

export { App };
