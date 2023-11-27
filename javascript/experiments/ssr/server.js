import path from 'path';
import express from 'express';
import { createElement as e } from 'react';
import reactDOMServer from 'react-dom/server';
import { App } from './App';
import { Page } from './Page';

const app = express();

app.use(express.static(path.join(__dirname, 'public')));

app.get('/', (req, res) => {
  const initialState = { name: 'World' };

  const { pipe } = reactDOMServer.renderToPipeableStream(
    e(Page, { title: 'Hello', initialState }, e(App)),
    {
      onShellReady() {
        pipe(res);
      },
    }
  );
});

app.listen(3000, () => {
  console.log('Server is listening on port: 3000');
});
