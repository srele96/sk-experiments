import { rspack, type Configuration, ExternalItem } from '@rspack/core';
import path from 'node:path';
import nodeExternals from 'webpack-node-externals';

const options: Configuration = {
  context: import.meta.dirname,
  target: 'node',
  externals: [nodeExternals() as ExternalItem],
  externalsPresets: {
    node: true,
  },
  plugins: [
    // todo: make class plugin for server, dont restart when hmr is enabled
  ],
};

const compiler = rspack(options);
