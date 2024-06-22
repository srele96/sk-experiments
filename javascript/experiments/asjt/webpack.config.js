const nodeExternals = require('webpack-node-externals');
const path = require('path');
const TenantPlugin = require('./TenantPlugin');

function createConfig(param) {
  const LOADER = 'loader';
  const PLUGIN = 'plugin';

  if (param != LOADER && param != PLUGIN) {
    throw new Error(
      `Invalid param received param=${param}.` +
        ` Valid params are: '${LOADER}' | '${PLUGIN}'`
    );
  }

  return {
    entry: `./index.${param}.js`,
    target: 'node',
    externals: [nodeExternals()],
    output: {
      path: path.resolve(
        __dirname,
        'dist',
        param,
        // Loader configuration requires only one build and resolves the rest
        // at runtime.
        param === LOADER ? '' : process.env.TENANT
      ),
      filename: 'build.js',
    },
    devtool: false, // Readable output.
    module: {
      rules: [
        param === LOADER && {
          test: /\.js$/,
          exclude: /node_modules/,
          use: {
            loader: require.resolve('./importReplaceLoader.js'),
          },
        },
      ].filter(Boolean),
    },
    plugins: [
      param === PLUGIN && new TenantPlugin({ tenant: process.env.TENANT }),
    ].filter(Boolean),
  };
}

const paramLoader = 'loader';
const paramPlugin = 'plugin';

module.exports = [createConfig(paramLoader), createConfig(paramPlugin)];
