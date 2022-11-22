const ReactRefreshWebpackPlugin = require('@pmmmwh/react-refresh-webpack-plugin');
const path = require('path');

/** @type {import('webpack').Configuration} */
const config = {
  // Don't care to change mode. This is demo.
  mode: 'development',
  entry: path.resolve('client.js'),
  // Use the same directory as the express server.
  output: {
    path: path.resolve(__dirname, 'public'),
    filename: 'bundle.js',
  },
  module: {
    rules: [
      {
        test: /\.js/,
        exclude: /node_modules/,
        use: [
          {
            loader: require.resolve('babel-loader'),
            options: {
              presets: [
                '@babel/preset-env',
                [
                  '@babel/preset-react',
                  {
                    runtime: 'automatic',
                    mode: 'development',
                  },
                ],
              ],
              plugins: [require.resolve('react-refresh/babel')],
            },
          },
        ],
      },
    ],
  },
  devServer: {
    hot: true,
  },
  plugins: [new ReactRefreshWebpackPlugin()],
};

module.exports = config;
