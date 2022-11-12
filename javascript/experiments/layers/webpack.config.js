const path = require('path');

/** @type {import('webpack').Configuration} */
module.exports = {
  mode: 'development',
  entry: path.resolve('src', 'index.js'),
  module: {
    rules: [
      {
        test: /\.js/,
        exclude: /node_modules/,
        use: {
          // Make sure the loader is installed.
          loader: require.resolve('swc-loader'),
        },
      },
    ],
  },
  devServer: {
    hot: true,
  },
};
