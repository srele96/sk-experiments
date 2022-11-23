const express = require('express');
const { createProxyMiddleware } = require('http-proxy-middleware');
const fs = require('fs/promises');
const path = require('path');

const app = express();
app.set('view engine', 'ejs');

// Use mock server data and render in template to prove that we are really
// using ReactJS, Webpack and Webpack Dev Server aside from template engine.
const people = [
  { id: '1', name: 'John' },
  { id: '2', name: 'Jane' },
  { id: '3', name: 'Caren' },
];

app.get('/', (req, res) => {
  // Get path to javascript files compiled by webpack and insert them.
  fs.readFile(path.resolve('public', 'manifest.json'))
    .then((webpackManifest) => {
      // Transform content of webpack manifest to javascript file paths.
      const scriptPaths = Object.values(JSON.parse(webpackManifest.toString()));

      // Serve some traditional server side page content...
      res.status(200);
      res.setHeader('Content-Type', 'text/html');
      res.render('index', { scriptPaths, people });
    })
    .catch((error) => {
      console.error(error);

      // Treat all errors as internal server error and provide feedback.
      res.status = 500;
      res.setHeader('Content-Type', 'text/html');
      res.send('Oops! Sorry, something went wrong.');
    });
});

// Place after every other request.
app.use(
  '*',
  createProxyMiddleware({
    // Hit webpack-dev-server.
    target: 'http://localhost:8080',
    // Use this option and whole middleware only in development.
    // The whole purpose of middleware is to retrieve the javascript files
    // that the webpack-dev-server compiles. Additionally, this allows us
    // to use HMR and fast refresh with another server aside of
    // webpack-dev-server.
    changeOrigin: true,
  })
);

/**
 * NOTE!!!
 *
 * The HMR throws an error because websockets fail to connect to:
 *
 * ws:localhost:3000/ws
 *
 * I assume that happens because we don't proxy WebSocket requests to the
 * webpack-dev-server WebSocket server.
 *
 * I tried to fix that by setting up two separate proxies.
 * - JavaScript content.
 * - HMR
 *
 * I tried to use regexes on app.use(/only_websockets_for_hrm/)
 * and app.use(/exclude_websocket_requests_for_the_rest/)
 * but I couldn't make that work and I didn't figure out why.
 *
 * I decided to stop because it became less fun the more time went on.
 */

app.listen(3000, () => console.log('http://localhost:3000'));
