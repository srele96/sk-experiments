const express = require('express');
const app = express();

app.use((req, res, next) => {
  res.setHeader('Access-Control-Allow-Origin', '*');
  next();
});

app.get('/', (req, res) => {
  res.send('Request to /');
});

app.get('/foo', (req, res) => {
  res.send('Request to /foo');
});

app.get('/bar', (req, res) => {
  res.send('Request to /bar');
});

app.listen(3000, () => {
  console.log('http://localhost:3000');
});
