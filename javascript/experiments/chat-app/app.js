const { Server } = require('socket.io');
const { createServer } = require('http');
const express = require('express');
const path = require('path');
const { renderToPipeableStream } = require('react-dom/server');
const { PageOne, PageTwo, DataContext } = require('./client');
const { useState } = require('react');

const css = new Set();
function insertCss(...styles) {
  styles.forEach((style) => css.add(style._getCss()));
}

console.log([...css].join(''));

const stream = renderToPipeableStream(
  <DataContext.Provider value={{ test: 'test' }}>
    <PageOne />
  </DataContext.Provider>,
  {
    onShellReady() {
      stream.pipe(process.stdout);
    },
  }
);

const app = express();

app.set('view engine', 'ejs');

app.use(express.static(path.join(__dirname, 'public')));

app.get('/', (_, response) => {
  const __INITIAL_DATA__ = { title: 'Chat App' };

  response.render('index', { __INITIAL_DATA__ });
});

const PORT = process.env.PORT ?? 3000;

const appServer = createServer(app);
const socketServer = new Server(appServer);

appServer.listen(PORT, () => {
  console.log(`Server started on: http://localhost:${PORT}/`);
});

socketServer.on('connection', (socket) => {
  console.log(`Socket id: ${socket.id} connected.`);
});
