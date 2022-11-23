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
  fs.readFile(path.resolve('dist', 'manifest.json'))
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
    // We have to proxy WebSocket requests to support Hot Module Reloading.
    // Without ws: true one of the compiled javascript files throw an error:
    // The connection to ws://localhost:3000/ws has failed. We can see that it
    // hits port 3000 which most likely means we have to proxy WebSocket
    // requests.
    ws: true,
  })
);

app.listen(3000, () => console.log('http://localhost:3000'));
