# How to read Webpack build JS files for React SSR

I found out I can get stats from the webpack build object. This is an attempt
to see how it works.

## What problems does this solve?

SSR requires an HTML template that references the file names. Webpack dev server
serves those files from the memory. One way to get them is to get the dev server
to write output to disk. However, writing to disk is slow. Alternative solution
and probably better is to read the files from webpack stats.

I actually read about this in some ReactJS blog post.

## Goals:

- Create as many js output files as possible.
- Code splitting, external dependencies, main bundle, etc...
- Get their file names and paths.
- Create a template component that receives rendered react app.

## References

- [Webpack - Stats Data](https://webpack.js.org/api/stats/)
