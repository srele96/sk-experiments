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
    .catch();
});

// Place after every other request.
app.use(
  '*',
  createProxyMiddleware({
    // Hit webpack-dev-server.
    target: 'http://localhost:8080',
    // Run this only in development, so we can treat webpack content as same origin.
    // Because in production we serve the webpack content from only one origin.
    changeOrigin: true,
  })
);

app.listen(3000, () => console.log('http://localhost:3000'));
