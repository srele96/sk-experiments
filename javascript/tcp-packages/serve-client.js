const { join } = require('path');
const express = require('express');
const serveClient = express();
serveClient.use(express.static(join(__dirname, 'public')));
serveClient.listen(3005, () => console.log('Server: http://localhost:3005'));
