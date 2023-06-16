# server-and-client

Play with server and client side rendering.

## Explanation

I wanted to play a bit with client and server side code. My intent was to cast some clarity on what the hell happens with files when webpack compiles them. So here we literally have folder `components` which contains code that is going to run inside `client.js` and `server.js`. That code is universal, isomorphic, or whatever, it simply is going to run in `NodeJS` and `Browser` environments.

The `webpack.config.js` also contains two compilation objects that each points to an entry for client and server.

## The flow is as follows

The `webpack.config.js` creates two objects each points to entry `client.js` and `server.js`. Then, we run the `yarn start` which is going to create two javascript files for us: `dist/public/client.js` and `dist/server.js`. After that, we are ready.

We should start the server environment: `node dist/server.js`. The reason will be explained after, it is not completely intuitive why we have to run that file.

Then the server `dist/server.js` is going to serve files statically from `dist/public` folder. We have to serve them like that because we receive all requests inside our `dist/server.js`.

## So, why do we have to use Webpack?

The code inside files in the `components/` directory is not compatible with `NodeJS` and `Browser` environment. Therefore, we have to make that code runnable in both of them. That is why we need to change it to code compatible with browser and nodejs.

## How to run

1. Make sure you have [NodeJS](https://nodejs.org/en/) and [Yarn](https://yarnpkg.com/getting-started/install) installed.
2. Run `yarn` to install dependencies.
3. Run `yarn start` to start watching the files.
4. Run `yarn server` to start the server.
