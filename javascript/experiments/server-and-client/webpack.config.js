const path = require('path');
const nodeExternals = require('webpack-node-externals');

/** @type {import('webpack').Configuration} */
const clientConfig = {
  mode: 'development',
  entry: path.join(__dirname, 'client.js'),
  output: {
    filename: 'client.js',
    path: path.resolve(__dirname, 'dist', 'public'),
  },
};

/** @type {import('webpack').Configuration} */
const serverConfig = {
  mode: 'development',
  target: 'node',
  entry: path.join(__dirname, 'server.js'),
  output: {
    filename: 'server.js',
    path: path.resolve(__dirname, 'dist'),
  },
  externals: [nodeExternals()],
};

module.exports = [clientConfig, serverConfig];
