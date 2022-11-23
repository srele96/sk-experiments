const express = require('express');
const { createProxyMiddleware } = require('http-proxy-middleware');
const fs = require('fs/promises');
const path = require('path');

const app = express();
app.set('view engine', 'ejs');

app.get('/', (req, res) => {
  // Get path to javascript files compiled by webpack and insert them.
  fs.readFile(path.resolve('public', 'manifest.json'))
    .then((webpackManifest) => {
      // Transform content of webpack manifest to javascript files.
      const scriptPaths = Object.values(JSON.parse(webpackManifest.toString()));

      // Serve some traditional server side page content...
      res.status(200);
      res.setHeader('Content-Type', 'text/html');
      res.render('index', { scriptPaths });
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

app.listen(3000, () => console.log('http://localhost:3000'));
