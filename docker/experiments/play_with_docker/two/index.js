// ----------------------------------------------------------------------------
// Ignore all good practices and make services as fast as possible to use with
// docker compose.
// ----------------------------------------------------------------------------

const axios = require('axios');
const express = require('express');
const app = express();

app.use((req, res, next) => {
  res.setHeader('Access-Control-Allow-Origin', '*');
  next();
});

const client = axios.create({
  baseURL: 'http://one:3000',
});

app.get('/', (req, res) => {
  client
    .get('/')
    .then((response) => {
      res.send(`Response data: ${response.data}`);
    })
    .catch((error) => {
      const errorInfo = error.toJSON();
      console.error(errorInfo);
      res.statusCode = 500;
      res.send(errorInfo.message);
    });
});

app.get('/foo', (req, res) => {
  client
    .get('/foo')
    .then((response) => {
      res.send(`Response data: ${response.data}`);
    })
    .catch((error) => {
      const errorInfo = error.toJSON();
      console.error(errorInfo);
      res.statusCode = 500;
      res.send(errorInfo.message);
    });
});

app.get('/bar', (req, res) => {
  client
    .get('/bar')
    .then((response) => {
      res.send(`Response data: ${response.data}`);
    })
    .catch((error) => {
      const errorInfo = error.toJSON();
      console.error(errorInfo);
      res.statusCode = 500;
      res.send(errorInfo.message);
    });
});

app.listen(4000, () => {
  console.log('http://localhost:4000');
});
