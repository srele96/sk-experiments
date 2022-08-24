// The source: https://nodejs.org/api/stream.html#api-for-stream-consumers
const http = require('http');

const server = http.createServer(
  function toUnderstandRequestAndResponseStreamRoleInDataFetching(req, res) {
    let body = '';
    let chunksReceived = 0;
    req.setEncoding('utf8');

    req.on('data', function saveChunkDataAndChunkCount(chunk) {
      body += chunk;
      chunksReceived += 1;
    });

    req.on('end', function sendReceivedChunkDataStatistic() {
      try {
        const chunkStatistic = JSON.stringify({
          chunkCount: chunksReceived,
          received: body,
        });

        res.writeHead(200, { 'Content-Type': 'application/json' });
        res.write(chunkStatistic);
        res.end();
      } catch (error) {
        // treat all errors as internal server error
        res.statusCode = 500;
        // let the user know what happened
        return res.end(error.message);
      }
    });
  }
);

const port = 3001;
server.listen(port);
