module.exports = function (api) {
  api.cache(true);

  const presets = [
    '@babel/preset-env',
    [
      '@babel/preset-react',
      {
        runtime: 'automatic',
        mode: 'development',
      },
    ],
  ];

  const plugins = [];

  return {
    presets,
    plugins,
  };
};
