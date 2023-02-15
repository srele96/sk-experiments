const { createElement: e, StrictMode } = require('react');
const { hydrateRoot } = require('react-dom/client');
const { RouterProvider, createBrowserRouter } = require('react-router-dom');
const { Home } = require('./components/Home');
const { About } = require('./components/About');

function renderApp() {
  const id = 'root';
  const domRoot = document.getElementById(id);

  hydrateRoot(
    domRoot,
    e(
      StrictMode,
      null,
      e(RouterProvider, {
        router: createBrowserRouter([
          { path: '/', element: e(Home) },
          { path: '/about', element: e(About) },
        ]),
      })
    )
  );
}

renderApp();
