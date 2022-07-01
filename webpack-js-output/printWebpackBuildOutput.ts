import webpack from 'webpack';

webpack({}, (error, stats) => {
  if (error) console.log('Error during Webpack compilation', error);
  else {
    // here we can read js output files and create our own html template
    console.log('Webpack compilation completed', stats.compilation.assets);
  }
});
