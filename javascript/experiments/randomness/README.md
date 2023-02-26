# Randomness

I was writing some random code for random idea for fun... I was bored as hell and didn't know what to do. I just let my mind wander and write some code out of blue.

## What is happening in this directory?

I wanted to use TypeScript, realized to use it with ReactJS and ReactDOM there were problem with their type declarations. I didn't want to mess with the type declarations so I decided to use Webpack to bundle the code. The library was missing type so I had to add type declaration, it looked like nice convention to use `@types` directory for that, because we install `@types/react` from npm. Using global `global.d.ts` to tell my app that there are type declarations for libraries. Telling typescript where to find the `global.d.ts`, etc... Extracting the old code to a JavaScript file to make it immediately obvious what's the content of `index.js` file.
