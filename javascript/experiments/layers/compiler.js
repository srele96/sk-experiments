import path from 'path';
import webpack from 'webpack';
import webpackDevMiddleware from 'webpack-dev-middleware';
import express from 'express';

const app = express();

const handleCompilationRequests = webpackDevMiddleware(
  webpack({
    entry: path.resolve('src', 'index.js'),
    mode: 'development',
  })
);

app.use(handleCompilationRequests);

/**
 *
 * @param {import('express').Request} _
 * @param {import('express').Response} res
 */
function renderTemplate(_, res) {
  handleCompilationRequests.waitUntilValid((stats) => {
    const createScriptTags = stats.toJson().assets.reduce((scripts, asset) => {
      return (scripts += `<script src="${asset.name}"></script>`);
    }, '');
    const template = `
      <!DOCTYPE html>
      <html lang="en">
        <head>
          <meta charset="UTF-8" />
          <meta
            name="viewport"
            content="width=device-width, initial-scale=1.0"
          />
        </head>
        <body>
          <div id="root"></div>
          ${createScriptTags}
        </body>
      </html>
    `;

    res.status = 200;
    res.setHeader('Content-Type', 'text/html');
    res.send(template);
  });
}

app.use(renderTemplate);

app.listen(3000, () => {
  console.log('Server started on: http://localhost:3000/');
});
