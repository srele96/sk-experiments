const nodeExternals = require('webpack-node-externals');

/** @type {import('webpack').Configuration} */
const clientConfig = {
  target: 'web',
  mode: 'development',
  entry: './client.js',
  output: {
    filename: 'client.js',
    path: __dirname + '/dist/public',
  },
};

/** @type {import('webpack').Configuration} */
const serverConfig = {
  target: 'node',
  mode: 'development',
  entry: './server.js',
  output: {
    filename: 'server.js',
    path: __dirname + '/dist',
  },
  externals: [nodeExternals()],
};

module.exports = [clientConfig, serverConfig];
