const express = require('express');
const path = require('path');
const app = express();

app.set('view engine', 'ejs');

app.use(express.static(path.join(__dirname, 'public')));

app.get('/', (_, res) => {
  res.render('chat');
});

const PORT = process.env.PORT ?? 3000;

app.listen(PORT, () => {
  console.log(`Server started on: http://localhost:${PORT}/`);
});
