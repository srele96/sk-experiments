import express from 'express';
import ReactDOMServer from 'react-dom/server';
import { Page } from './Page';
import { ShellErrorClientRenderer } from './ShellErrorClientRenderer';

const app = express();

app.get('/', (_, res) => {
  let didError: boolean = false;

  const { pipe } = ReactDOMServer.renderToPipeableStream(
    <Page title="Home">
      <h1>Home</h1>
    </Page>,
    {
      onAllReady() {
        res.statusCode = didError ? 500 : 200;
        res.setHeader('Content-Type', 'text/html; charset=utf-8');
        pipe(res);
      },
      onShellError() {
        res.statusCode = 500;
        res.setHeader('Content-Type', 'text/html; charset=utf-8');
        // should always be renderable to allow client to take over
        res.send(ReactDOMServer.renderToString(<ShellErrorClientRenderer />));
      },
      onError(error) {
        didError = true;
        console.error(error);
      },
    }
  );
});

app.listen(3000, () => console.log('http://localhost:3000/'));
