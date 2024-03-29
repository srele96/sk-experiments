const path = require('path');
const HtmlWebpackPlugin = require('html-webpack-plugin');
const ReactRefreshWebpackPlugin = require('@pmmmwh/react-refresh-webpack-plugin');

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
      {
        test: /\.scss/,
        use: [
          require.resolve('style-loader'),
          {
            loader: require.resolve('css-loader'),
            options: {
              modules: {
                exportLocalsConvention: 'camelCase',
              },
            },
          },
          require.resolve('sass-loader'),
        ],
      },
    ],
  },
  devServer: {
    hot: true,
  },
  plugins: [
    new ReactRefreshWebpackPlugin(),
    new HtmlWebpackPlugin({
      template: path.resolve('public', 'index.html'),
    }),
  ],
};
