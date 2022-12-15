const { Server } = require('socket.io');
const { createServer } = require('http');
const express = require('express');
const path = require('path');

const app = express();

app.set('view engine', 'ejs');

app.use(express.static(path.join(__dirname, 'public')));

app.get('/', (_, res) => {
  res.render('index');
});

const PORT = process.env.PORT ?? 3000;

const server = createServer(app);
const io = new Server(server);

server.listen(PORT, () => {
  console.log(`Server started on: http://localhost:${PORT}/`);
});

io.on('connection', (socket) => {
  console.log(`Socket id: ${socket.id} connected.`);
});
