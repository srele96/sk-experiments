# JSONP

We will need:

## A client with a script:

```html
<script src="/jsonp-static"></script>
```

## A server with a route:

```js
const app = require('express')();
app.get('/jsonp-static', (req, res) => {
  res.send(`jsonp({ data: 'data' })`);
});
```

## What happens?

A script targeting a request that returns a string that is a function call
tries to call that function on the client.

If that function doesn't exist on the client, we get the reference error.

It appears that we _"call"_ client function from the server. That call happens
when a script points to a request that returns a string like function call.

## Return JavaScript code from the server

The code is only text. We can transfer it however we wish. Once the script
receives the code, it tries to run it.
