# Express is essentially a series of middleware calls

This statement intrigued me and I decided to try it out and see how does it really work.

This page on express site contains that statement [express guide - using middleware](https://expressjs.com/en/guide/using-middleware.html)

## server.js demonstrates call of 3 middlewares

Conclusion is that middleware is called between requests for whichever route, it is important in which order they are set.

Express indeed is really flexible framework with little functionality on its own.
