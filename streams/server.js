const stream = require('stream');
const createReadStream = require('fs').createReadStream;
const join = require('path').join;
const express = require('express');
const app = express();
console.log(stream);
app.use(express.static('public'));

app.get('/stream', (req, res) => {
  createReadStream(join(__dirname, 'users.json')).pipe(res);
});

app.listen(3000, () => {
  console.log('Server is running on port 3000');
});
