import express from 'express';
import webpack from 'webpack';
import webpackDevMiddleware from 'webpack-dev-middleware';
import webpackHotMiddleware from 'webpack-hot-middleware';

import { createElement as e, Fragment } from 'react';
import { renderToString } from 'react-dom/server';
import { ServerStyleSheet } from 'styled-components';
import { App } from './App';

const webpackClientConfig = require('./webpack.client.config');

const app = express();
const compiler = webpack(webpackClientConfig);

const middleware = webpackDevMiddleware(compiler, {
  publicPath: webpackClientConfig.output.publicPath,
});

app.set('view engine', 'ejs');

app.use(
  webpackDevMiddleware(compiler, {
    publicPath: webpackClientConfig.output.publicPath,
  })
);

app.use(
  webpackHotMiddleware(compiler, {
    path: '/__webpack_hmr',
  })
);

app.get('/', (req, res) => {
  middleware.waitUntilValid((stats) => {
    const sheet = new ServerStyleSheet();

    try {
      const html = renderToString(sheet.collectStyles(e(App)));
      const styleTags = sheet.getStyleTags();
      const scripts = stats
        .toJson()
        .assets.filter((asset) => asset.name.endsWith('.js'))
        .map((asset) => `<script src="${asset.name}"></script>`)
        .join('');

      res.render('index', {
        title: 'styled components',
        html,
        styleTags,
        scripts,
      });
    } catch (error) {
      console.error(error);
    } finally {
      sheet.seal();
    }
  });
});

const port = 3000;
app.listen(port, () => {
  console.log(`Server is listening on port ${port}`);
});
