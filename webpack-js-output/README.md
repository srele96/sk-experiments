# How to read JavaScript files from Webpack build while they are in memory

I found out I can get stats from the webpack build object. This is an attempt
to see how it works.

## Goals:

- Create as many js output files as possible.
- Code splitting, external dependencies, main bundle, etc...
- Get their file names and paths.
- Create a template component that receives rendered react app.

## References

- [Webpack - Stats Data](https://webpack.js.org/api/stats/)
