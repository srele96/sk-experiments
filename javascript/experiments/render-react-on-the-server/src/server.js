import express from 'express';
import { renderToPipeableStream } from 'react-dom/server';

import { Chrome } from './Chrome';
import { Page } from './Page';

const app = express();

app.get('/', (_, res) => {
  let didError = false;

  // Now... it is a really good question.
  // Should I fetch data and call renderToPipeable stream after.
  // Or should I fetch the data elsewhere?
  const { pipe } = renderToPipeableStream(
    <Chrome title="Render React on Server">
      <Page
        title="Render React on Server"
        content="Setting up React Server Side Rendering has never been easier!"
      />
    </Chrome>,
    // No clue how to use the options. I copied them from React documentation.
    // https://reactjs.org/docs/react-dom-server.html#rendertopipeablestream
    {
      onAllReady() {
        res.statusCode = didError ? 500 : 200;
        res.setHeader('Content-Type', 'text/html');
        pipe(res);
      },
      onError(error) {
        didError = true;
        console.error(error);
      },
    }
  );
});

app.listen(3000, () => console.log('Server started on htpp://localhost:3000/'));
