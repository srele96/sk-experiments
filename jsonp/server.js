const express = require('express');
const { join } = require('path');
const app = express();

app.use(express.static('public'));

app.get('/jsonp_static', (req, res) => {
  res.send(`jsonp({ foo: 'foo' })`);
});

app.listen(3000, () => console.log('server: http://localhost:3000'));
