const path = require('path');

// enable determinstic build
module.exports = function (env, args) {
  const isProduction = args.mode === 'production';

  const config = {
    entry: {
      app: path.resolve(__dirname, 'src', 'index.js'),
    },
    // enable bundling for both modes to compare output
    output: {
      filename: `${isProduction ? 'production' : 'development'}.bundle.js`,
      path: path.resolve(
        __dirname,
        isProduction ? 'production' : 'development'
      ),
      clean: true,
    },
    module: {
      rules: [
        // enable transpilation of modern js and react
        {
          test: /\.js$/,
          exclude: /node_modules/,
          use: {
            loader: 'babel-loader',
            options: {
              presets: ['@babel/preset-env', ['@babel/preset-react']],
            },
          },
        },
      ],
    },
    mode: isProduction ? 'production' : 'development',
    optimization: {
      // allows me to see comments in the bundle for unused
      // exports like: /* unused harmony export App */
      usedExports: true,
    },
    // provides readable output code in development bundle
    devtool: false,
  };

  return config;
};
