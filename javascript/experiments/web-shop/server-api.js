const express = require('express');
const app = express();

app.get('/api/v1/foo', (_, res) => {
  res.send('Hello!');
});

app.listen(5000, () => console.log('Server API -> http://localhost:5000'));
