import express from 'express';
import path from 'path';
import { renderToStaticMarkup } from 'react-dom/server';

const app = express();

function App() {
  return <h1>Hello World, change??hello? asd???</h1>;
}

const port = process.env.PORT ?? 3000;

app.use(express.static(path.join(__dirname, 'public')));

app.get('/foo', (req, res) => {
  res.send(renderToStaticMarkup(<App />));
});

const server = app.listen(port, () => {
  console.log(`Example app listening on port ${port}`);
});

if (import.meta.webpackHot) {
  import.meta.webpackHot.accept();
  import.meta.webpackHot.dispose(() => {
    server.close(() => {
      console.log('server closed');
    });
  });
}
