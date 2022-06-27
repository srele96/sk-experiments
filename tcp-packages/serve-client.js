const { join } = require('path');
const express = require('express');
const server = express();
server.use(express.static(join(__dirname, 'public')));
server.listen(3005, () => console.log('Server: http://localhost:3005'));
