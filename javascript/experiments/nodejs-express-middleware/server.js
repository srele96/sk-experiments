const express = require('express');
const app = express();

// Express is just a series of middleware calls, hmmm...
// Here, only middleware is registered
// nothing like app.get(/* ... params */) or app.post(/* ... params */)
// but when we open http://localhost:3000 in browser, then look at the console
// the output is:
// First middleware GET
// Second middleware GET
app.use(
  (req, res, next) => {
    console.log('First middleware', req.method);
    return next();
  },
  (req, res, next) => {
    console.log('Second middleware', req.method);
    return next();
  },
  (req, res, next) => {
    res.send(`Hello from ${req.method} 
    request to ${req.url}`);
  }
);

app.listen(3000, () => console.log('Server started on: http://localhost:3000'));
