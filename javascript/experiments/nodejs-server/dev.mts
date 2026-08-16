import { type ExternalItem, type RspackOptions, rspack } from '@rspack/core';
import { RunScriptWebpackPlugin } from 'run-script-webpack-plugin';
import { ReactRefreshRspackPlugin } from '@rspack/plugin-react-refresh';
import path from 'node:path';

import nodeExternals from 'webpack-node-externals';

const isDev = process.env.NODE_ENV === 'development';
const root = import.meta.dirname;

const swcRule = (refresh: boolean = false) => ({
  test: /\.(?:js|mjs|ts|tsx)$/,
  exclude: [/node_modules/],
  loader: 'builtin:swc-loader',
  options: {
    jsc: {
      transform: {
        react: {
          runtime: 'automatic',
          development: isDev,
          // prolly false for server build?
          refresh,
        },
      },
    },
  },
});

const clientConfig: RspackOptions = {
  name: 'client',
  mode: isDev ? 'development' : 'production',
  context: root,
  target: 'web',
  entry: {
    client: './client.tsx',
  },
  resolve: {
    extensions: ['...', '.ts', '.tsx', '.js'],
  },
  output: {
    path: path.resolve(root, 'dist', 'public'),
    publicPath: '/',
    filename: isDev ? '[name].js' : '[name].[contenthash:8].js',
    chunkFilename: isDev ? '[name].chunk.js' : '[name].[contenthash:8].js',
    clean: true,
  },
  optimization: {
    runtimeChunk: 'single',
    moduleIds: isDev ? 'named' : 'deterministic',
    chunkIds: isDev ? 'named' : 'deterministic',
    splitChunks: {
      chunks: 'all',
      cacheGroups: {
        react: {
          test: /[\\/]node_modules[\\/](react|react-dom|scheduler)[\\/]/,
          name: 'react',
          priority: 40,
          enforce: true,
        },
        vendor: {
          test: /[\\/]node_modules[\\/]/,
          name: 'vendor',
          priority: 20,
        },
        common: {
          minChunks: 2,
          priority: 10,
          reuseExistingChunk: true,
        },
      },
    },
  },
  module: {
    rules: [swcRule(isDev)],
  },
  plugins: [isDev && new ReactRefreshRspackPlugin()],
};

const serverConfig: RspackOptions = {
  mode: isDev ? 'development' : 'production',
  dependencies: ['client'],
  name: 'server',
  entry: {
    server: isDev
      ? ['@rspack/core/hot/poll?100', './server.tsx']
      : './server.tsx',
  },
  context: root,
  target: 'node',
  externals: [
    nodeExternals({
      allowlist: [/@rspack\/core\/hot\/poll/],
    }) as ExternalItem,
  ],
  externalsPresets: {
    node: true,
  },
  resolve: {
    extensions: ['...', '.ts', '.tsx', '.js'],
  },
  output: {
    path: path.resolve(root, 'dist', 'server'),
    filename: 'server.js',
    clean: true,
  },
  module: {
    rules: [
      swcRule(),
      {
        test: /\.node$/,
        type: 'asset/resource',
      },
    ],
  },
  plugins: [
    isDev && new rspack.HotModuleReplacementPlugin(),
    isDev &&
      new RunScriptWebpackPlugin({
        name: 'server.js',
        // false while HMR is enabled
        autoRestart: false,
      }),
  ],
};

const compiler = rspack([clientConfig, serverConfig]);

const watching = compiler.watch({ aggregateTimeout: 300 }, (err, stats) => {
  if (err) {
    console.error('A compiler error occured for this run', err);
    return;
  }

  if (!stats) {
    console.warn('Stats missing for this run.');
    return;
  }

  const json = stats.toJson({});

  for (const child of json.children ?? []) {
    if (child.warnings?.length) {
      console.warn(`[${child.name}] warnings:`);
      console.warn(child.warnings);
    }
    if (child.errors?.length) {
      console.error(`[${child.name}] errors:`);
      console.error(child.errors);
    }
  }

  console.log(stats.toString({ colors: true }));
});

const close = () => {
  watching.close(() => {
    compiler.purgeInputFileSystem();
    process.exit(0);
  });
};

process.on('SIGTERM', close);
process.on('SIGINT', close);
