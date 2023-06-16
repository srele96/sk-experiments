const express = require('express');
const { join } = require('path');
const app = express();

app.use(express.static('public'));

app.get('/jsonp-static', (req, res) => {
  res.send(`jsonp({ foo: 'foo' })`);
});

app.get('/js-code', (req, res) => {
  res.send(`
    console.log(
      'Hi there! A script <script src="js-code"></script> will run me'
    );

    function iCanDoAnything() {
      // i can add an element
      const body = document.getElementsByTagName('body')[0];
      const h1 = document.createElement('h1');

      h1.innerText = 'Daayum! I really can do anything.';

      body.appendChild(h1);
    }

    iCanDoAnything();
  `);
});

app.listen(3000, () => console.log('server: http://localhost:3000'));
