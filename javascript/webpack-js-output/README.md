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

## Outcome

My code is not compatible with SSR setup. I started with intention to inspect
the files from compilation object. Because I started with that intention, the
code only does that.

I realized that my code is not compatible when I started thinking what do I
need for proper webpack ssr & csr setup. Oops.

Define your requirements well :)

## References

- [Webpack - Stats Data](https://webpack.js.org/api/stats/)
