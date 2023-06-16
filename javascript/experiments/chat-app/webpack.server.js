const nodeExternals = require('webpack-node-externals');

/** @type {import('webpack').Configuration} */
const config = {
  entry: './app.js',
  mode: 'development',
  output: {
    filename: 'server.js',
  },
  module: {
    rules: [
      {
        test: /\.js$/,
        exclude: /node_modules/,
        use: {
          loader: require.resolve('babel-loader'),
          options: {
            presets: [
              '@babel/preset-env',
              [
                '@babel/preset-react',
                {
                  runtime: 'automatic',
                },
              ],
            ],
          },
        },
      },
      {
        test: /\.css$/i,
        use: [
          require.resolve('isomorphic-style-loader'),
          {
            loader: require.resolve('css-loader'),
            options: {
              modules: true,
            },
          },
        ],
      },
    ],
  },
  // provide readable output
  devtool: false,
  externalsPresets: {
    node: true,
  },
  externals: [nodeExternals()],
};

module.exports = config;
