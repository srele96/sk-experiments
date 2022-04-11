# Webpack bundling process

In this package I have researched how does Webpack bundling process work in order to understand optimization of frontend web applications.

## Note

Production and development outputs are not gitignored so anyone reading source code can see the output without cloning/forking and building code locally.

## Instructions to run the code

_This project uses **Yarn** so you will need it to run it._

### If you are using yarn:

1. Make sure you are in root directory
2. Run `yarn install`
3. Run `cd yes-module/webpack-bundling-process`
4. Run `yarn build`

### If you are using npm

_I do not guarantee this will work._

1. Make sure you are in root directory
2. In root directory delete `yarn.lock` and `.yarnrc.yml`
3. Run `npm install`
4. Run `cd yes-module/webpack-bundling-process`
5. Run `npm run build`

## Covered topics

- After bundling, modules are stored in object as key, value pairs
- Webpack uses it's own functions for export/import in final bundle
- Configuration enables infinite optimization possibilities, which is why webpack is powerfull
- Webpack dynamic import uses promises in final bundle to load the code
- Output is much smaller in production mode
- It is beneficial to split node_modules from main bundle for better user experience
- Transpilation of react code
- Bundle inclusion of react code from node_modules

### After bundling, modules are stored in object as key, value pairs

This discovery helps me understand how optimization works.

JavaScript file size depends on amount of characters in the file, large applications have a lot of code which results in a lot of characters and sizable output files.

Benefits of minification is usage of one letter variables, functions, etc... This reduces bundle size.

I am not sure how does code splitting benefit us but i'd assume it is required when it is needed, which is why it is in another file. When main bundle requires code that has been dynamically imported, I assume it is used only then.

Another assumpion is that SSR doesn't work with webpack code splitting because server imports whole page, but how does it handle splitted files? How can it know what is or isn't split?

I guess it would end up sending more than required by frontend, which is what was solved by loadable library.

### It is beneficial to split node_modules from main bundle for better user experience

If not split, node_modules code required by our application will be bundled together with the rest of our application.

This can be seen in development bundle.

However, i assume splitting this works in similar way like dynamic imports, but goes through configuration file.
