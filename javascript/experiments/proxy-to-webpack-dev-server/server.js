const express = require('express');
const { createProxyMiddleware } = require('http-proxy-middleware');

const app = express();

app.get('/', (req, res) => {
  // Serve some traditional server side page content...
  res.status(200);
  res.setHeader('Content-Type', 'text/html');
  res.send('<h1>Hello World!</h1>');
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
