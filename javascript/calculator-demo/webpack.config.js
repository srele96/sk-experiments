const resolve = require('path').resolve;

// References:
// https://webpack.js.org/configuration/configuration-types/
// https://webpack.js.org/guides/author-libraries/
function createDevOrProdBuild(_, args) {
  const BUILD_MODE = args.mode;
  const isCorrectBuildMode =
    BUILD_MODE === 'development' || BUILD_MODE === 'production';

  if (isCorrectBuildMode)
    return {
      entry: resolve(__dirname, 'packages', 'calculator', 'index.js'),
      output: {
        path: resolve(__dirname, 'dist'),
        filename: 'calculator.' + BUILD_MODE + '.js',
        library: {
          name: 'calculator',
          type: 'umd',
        },
      },
    };
  else
    throw new Error(
      'Please provide correct build mode, received: ' + BUILD_MODE
    );
}

module.exports = createDevOrProdBuild;
