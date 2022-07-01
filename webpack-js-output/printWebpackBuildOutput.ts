import webpack, { Configuration } from 'webpack';
import { join } from 'path';

const config: Configuration = {
  mode: 'development',
  // Don't wanna setup ts for the app code. I want typed stats to know what I
  // can expect.
  entry: require.resolve('./src/index.js'),
  output: {
    clean: true,
    path: join(__dirname, 'dist'),
    // Split every other directory to check do I receive file paths or just
    // the file names.
    filename: (pathData) => {
      return pathData.chunk.name === 'main' ? '[name].js' : 'assets/[name].js';
    },
  },
  // I want to split chunks as much as possible for the sake of seeing the
  // files in stats.
  optimization: {
    runtimeChunk: 'single',
    splitChunks: {
      chunks: 'all',
    },
  },
};

// Read the js output files from webpack stats, build or wherever.
webpack(config, (error, stats) => {
  if (error) console.log('Error during Webpack compilation', error);
  else {
    // here we can read js output files and create our own html template
    const compiledFileNames = Object.keys(stats.compilation.assets);
    console.log('Webpack compilation completed', compiledFileNames);
  }
});
