/**
 * Documentation below.
 *
 * Disclaimer: Code in this file is mumbo-jumbo and I do not care as I got it to
 * work and do what I want, so I can continue working on algorithmic problems.
 * Althrough extremely challenging, I could not let this problem go until I have
 * found satisfying solution. Current one does not entirely give me a sense of
 * satisfaction, however I am fairly FINE with how it turned out.
 *
 * So, how does it work?
 *
 * Loader runs before plugins, therefore any code modification will go through
 * all regular webpack processes.
 * That solves plenty of problems I had while modifying code within plugins.
 * Perhaps I find module easy to solve the problem of tenant overriding because
 * I have gone through a lot of suffering with plugin system.
 * Plugins receive webpack state through various methods. Modifying Abstract
 * Syntax Tree could be a way to go, if webpack didn't have custom attributes on
 * it.
 * I wasn't sure whether I could alter it safely and have the plugin work.
 * Modifying imports using Dependency Templates didn't work because injecting an
 * import that references a new file didn't add the new file to the webpack
 * output. Debugging webpack plugins takes days, for reference it took me one
 * day to figure out why dependency wasn't retrieveable using
 * `moduleGraph.getModule(dep)`.
 * After all the trouble I realized I could utilize the idea of magic comments
 * and loaders. There are plenty of problems with that as well. Non-Unique
 * comments, configuration in comment isn't nice developer experience, parsing
 * configuration from comments. Using Abstract Syntax Tree parser would've been
 * the best solution. Alternatively a really well crafted regex could extract
 * all comments. However I feel like parsing would yield much better results as
 * it would allow us to replace the comment much more safely than regex as we
 * have the exact location and information about the comment location in the
 * code.
 *
 * How does the plugin work?
 *
 *  - Handle only one specific case in index.js
 *  - Parse the code and look for variable with a specific name
 *  - Find an importPath defined inside the config object
 *  - Extract the import path from the config object
 *  - Check if there's `tenant` directory in the imported path
 *    - If yes, inject code for loading code from desired tenant
 *    - Otherwise, inject code for loading code from initial path
 *  - User provides callback that we can set as we load modules, so we hand over
 *    the modules to the user
 **/
const { parse } = require('@babel/parser');
const traverse = require('@babel/traverse').default;
const t = require('@babel/types');
const path = require('path');
const fs = require('fs');

module.exports = function myLoader(source) {
  // Don't handle cases that make sense, only this one that I want to try out.
  traverse(parse(source, { sourceType: 'module' }), {
    // Look for a declaration of a configuration variable
    VariableDeclarator(parsedPath) {
      if (t.identifier(parsedPath.node.type)) {
        const OVERRIDE_CONFIG_VARNAME = '__OVERRIDE__CONFIG__';
        // If the variable we require is defined by the user
        if (parsedPath.node.id.name === OVERRIDE_CONFIG_VARNAME) {
          if (t.objectExpression(parsedPath.node.init.properties)) {
            // Look for import path
            parsedPath.node.init.properties.forEach((property) => {
              const IMPORT_PATH_VARNAME = 'importPath';
              if (property.key.name == IMPORT_PATH_VARNAME) {
                const importPath = property.value.value;

                // Inject import code
                const tenantOverride =
                  path.dirname(importPath) + path.sep + 'tenant';
                const { base } = path.parse(importPath);
                if (fs.existsSync(tenantOverride)) {
                  const code = `
                  ;(function() {
                    const { RUNTIME_TENANT } = process.env;
                    if (process.env.RUNTIME_TENANT) {
                      console.log('Running mod for RUNTIME_TENANT=' + RUNTIME_TENANT);
                      import('./src/tenant/' + RUNTIME_TENANT + '/${base}')
                        .then(__on_module__)
                        .catch(__on_error__);
                    } else {
                      __on_module__(require('${importPath}'));
                    }
                  })();
                  `;
                  source += code;
                } else {
                  const code = `
                    ;(function() {
                      const wtf = require('${importPath}');
                      // We just assume the __on_module__ is defined by the user.
                      __on_module__(wtf);
                    })();
                  `;
                  source += code;
                }
              }
            });
          }
        }
      }
    },
  });

  return source;
};
