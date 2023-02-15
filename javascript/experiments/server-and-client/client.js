const { createElement: e } = require('react');
const { hydrateRoot } = require('react-dom/client');
const { App } = require('./App');

function renderApp() {
  const id = 'root';
  const domRoot = document.getElementById(id);
  hydrateRoot(domRoot, e(App));
}

renderApp();
