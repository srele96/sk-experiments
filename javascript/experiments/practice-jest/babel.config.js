module.exports = function (api) {
  api.cache(true);

  // Provide better typings for the config object.
  /** @type {import('@babel/core').TransformOptions}*/
  const config = {
    presets: ['@babel/preset-env'],
    plugins: [],
  };

  return config;
};
