const { Server } = require('socket.io');
const { createServer } = require('http');
const express = require('express');
const path = require('path');

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
