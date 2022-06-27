const serveData = require('express')();

serveData.get('*', (_, res) => {
  res.setHeader('Access-Control-Allow-Origin', '*');
  res.setHeader('Content-Type', 'application/json');
  res.status(200);
  res.send({ data: 'foo' });
});

serveData.listen(3000, () => console.log('Server: http://localhost:3000'));
