import path from 'path';
import webpack from 'webpack';
import webpackDevMiddleware from 'webpack-dev-middleware';
import express from 'express';
import { renderToPipeableStream } from 'react-dom/server';
import { App } from './src/App';

const app = express();

const handleCompilationRequests = webpackDevMiddleware(
  webpack({
    entry: path.resolve('src', 'index.js'),
    mode: 'development',
    module: {
      rules: [
        {
          test: /\.js/,
          exclude: /node_modules/,
          use: {
            loader: 'babel-loader',
          },
        },
      ],
    },
  })
);

app.use(handleCompilationRequests);

function Template(props) {
  return (
    <html lang="en">
      <head>
        <meta charSet="UTF-8" />
        <meta name="viewport" content="width=device-width, initial-scale=1.0" />
      </head>
      <body>
        <div id="root">{props.children}</div>
        {props.scripts}
      </body>
    </html>
  );
}

/**
 *
 * @param {import('express').Request} _
 * @param {import('express').Response} res
 */
function renderTemplate(_, res) {
  handleCompilationRequests.waitUntilValid((stats) => {
    const createScriptTags = stats.toJson().assets.reduce((scripts, asset) => {
      scripts.push(<script key={asset.name} src={asset.name}></script>);
      return scripts;
    }, []);

    const stream = renderToPipeableStream(
      <Template scripts={<>{createScriptTags}</>}>
        <App />
      </Template>,
      {
        onShellReady() {
          res.status = 200;
          res.setHeader('Content-Type', 'text/html');
          stream.pipe(res);
        },
      }
    );
  });
}

app.use(renderTemplate);

app.listen(3000, () => {
  console.log('Server started on: http://localhost:3000/');
});
