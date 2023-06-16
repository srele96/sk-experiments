const { createElement: e } = require('react');
const { renderToPipeableStream } = require('react-dom/server');
const { StaticRouter } = require('react-router-dom/server');
const path = require('path');
const express = require('express');
const app = express();
const { Home } = require('./components/Home');
const { About } = require('./components/About');

// We don't really live in the root directory as it may seem. Since we bundle
// the server using Webpack, we really run the server in another directory. We
// want to statically server the client bundle created by the Webpack.
app.use(express.static(path.join(__dirname, 'public')));

/**
 * @param {Object} props
 * @param {import('react').ReactNode} props.children
 **/
function Chrome(props) {
  return e(
    'html',
    null,
    e(
      'head',
      null,
      e('meta', { charSet: 'utf-8' }),
      e('meta', {
        name: 'viewport',
        content: 'width=device-width, initial-scale=1',
      })
    ),
    e('body', null, e('div', { id: 'root' }, props.children))
  );
}

function renderPage(element) {
  /**
   * @param {import('express').Request} request
   * @param {import('express').Response} response
   */
  function requestHandler(request, response) {
    const stream = renderToPipeableStream(
      e(StaticRouter, { location: request.url }, e(Chrome, null, element)),
      {
        bootstrapScripts: ['client.js'],
        onAllReady() {
          console.log('all ready');
        },
        onShellError(error) {
          const internalServerError = 500;
          response.statusCode = internalServerError;
          response.setHeader('content-type', 'text/html');
          const simpleFallbackErrorPage = '<h1>Something went wrong.</h1>';
          response.send(simpleFallbackErrorPage);
        },
        onShellReady() {
          response.setHeader('content-type', 'text/html');
          stream.pipe(response);
        },
      }
    );
  }

  return requestHandler;
}

app.get('/', renderPage(e(Home)));
app.get('/about', renderPage(e(About)));

const PORT = 3000;
app.listen(PORT, () => console.log(`Server on: http://localhost:${PORT}`));
