import express from 'express';
const app = express();

app.get('/', (_, res) => {
  res.send('hello asd');
});

app.listen(3000, () => console.log('http://localhost:3000/'));
