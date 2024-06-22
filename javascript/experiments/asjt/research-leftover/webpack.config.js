/******************************************************************************
 * ****************************************************************************
 * ****************************************************************************
 *
 * Research leftover documentation.
 *
 * ****************************************************************************
 *
 * The code in this file is valuable research and learning material. Here are
 * the methods I tried to apply to make the final version of the tenant
 * overriding system.
 * Without these, the final version of the code would not live to see the light.
 * All final ideas built up on the results of research in this file.
 * This file stores all the hard work preceeding the final result and is hence
 * the most valuable asset of the whole repo in my opinion.
 * I usually use research leftovers to further my knowledge, how?
 *  - I read the code in this file.
 *  - I get an idea, for example:
 *   - What can I use `moduleGraph` for?
 *   - Why does `dependencyTemplates` work?
 *   - Why do I have to structure dependencyTemplates the way I did?
 *   - etc...
 *  - I read webpack repo to find answer, google blogs, ask ChatGPT, think how
 *    would I implement given feature? Anything that comes to mind.
 * These methods are valuable because they allow me to expand previous
 * knowledge. I append new knowledge to the previous experiences.
 * Literally practice in any way I want. I do not bind myself to restricting
 * "I have to make a project and drive it to completion". I do what I want,
 * however I want, until whenver I want, infinitely... Restrictions are
 * pointless.
 *
 * ***************************************************************************
 * ***************************************************************************
 *****************************************************************************/
const JavascriptParser = require('webpack/lib/javascript/JavascriptParser');
const acorn = require('acorn');
const { simple: walk } = require('acorn-walk');
const Compilation = require('webpack/lib/Compilation');
const { RawSource } = require('webpack-sources');
const ConstDependency = require('webpack/lib/dependencies/ConstDependency');
const ModuleDependency = require('webpack/lib/dependencies/ModuleDependency');
const NullDependency = require('webpack/lib/dependencies/NullDependency');
const Dependency = require('webpack/lib/Dependency');
const {
  JAVASCRIPT_MODULE_TYPE_AUTO,
  JAVASCRIPT_MODULE_TYPE_DYNAMIC,
  JAVASCRIPT_MODULE_TYPE_ESM,
} = require('webpack/lib/ModuleTypeConstants');
const astring = require('astring');
const { parse } = require('@babel/parser');
const generate = require('@babel/generator').default;
const traverse = require('@babel/traverse').default;
const t = require('@babel/types');
const serialize = require('serialize-javascript');
const nodeExternals = require('webpack-node-externals');
const fs = require('fs');
const path = require('path');
const { inspect } = require('util');

class Something {
  PLUGIN_NAME = 'Something';

  apply(compiler) {
    compiler.hooks.compilation.tap(
      this.PLUGIN_NAME,
      (compilation, { normalModuleFactory }) => {
        // const logger = compilation.getLogger(this.PLUGIN_NAME);
        // compilation.dependencyTemplates.set(
        //   ConstDependency,
        //   new ConstDependency.Template()
        // )
        //

        // const handler = parser => {
        //   console.log({  })
        //   parser.hooks.expression.for(this).tap(this.PLUGIN_NAME, (expr) => {
        //     console.log({expr})
        //   })
        // };
        //
        // normalModuleFactory.hooks.parser
        //  .for(JAVASCRIPT_MODULE_TYPE_AUTO)
        //  .tap(this.PLUGIN_NAME, handler)

        compilation.hooks.buildModule.tap(this.PLUGIN_NAME, (module) => {
          // console.log({ buildModule: module })
          // console.log('module.parser.hooks', module.parser.hooks)
          // console.log(module.parser.hooks.program, 'here')
          module.parser.hooks.program.tap(this.PLUGIN_NAME, (parser) => {
            // console.log(module.request, { parser }, parser.body)
          });
          // See how does program.compile work
        });
        compilation.hooks.succeedModule.tap(this.PLUGIN_NAME, (module) => {
          // console.log({ succeedModule: module }) // Compilation.codeGenerationResults is null at this point
        });
        normalModuleFactory.hooks.parser
          .for(JAVASCRIPT_MODULE_TYPE_AUTO)
          .tap(this.PLUGIN_NAME, (parser) => {
            // console.log(ast.body)
          });
        normalModuleFactory.hooks.parser
          .for(JAVASCRIPT_MODULE_TYPE_DYNAMIC)
          .tap(this.PLUGIN_NAME, (parser) => {
            // console.log({ parser, JAVASCRIPT_MODULE_TYPE_DYNAMIC})
          });
        normalModuleFactory.hooks.parser
          .for(JAVASCRIPT_MODULE_TYPE_ESM)
          .tap(this.PLUGIN_NAME, (parser) => {
            // console.log({ parser, JAVASCRIPT_MODULE_TYPE_ESM })
          });
      }
    );
  }
}

//class CustomDependency extends ConstDependency {
//  constructor(code) {
//    super();
//    this._code = code;
//  }
//
//  code() {
//    return this._code;
//  }
//}
//
//CustomDependency.Template = class CustomDependencyTemplate extends (
//  ConstDependency.Template
//) {
//  apply(customDependency, source) {
//    console.log('insert code', customDependency.code()); // Ah Awesome!!!
//    // Yay!!! It works!!! It added code to each module!!! Oh My God!!! It Works!!!
//    source.insert(0, customDependency.code());
//  }
//};

//class CustomDependency extends ModuleDependency {
//  constructor(request, code) {
//    super(request);
//    console.log('dependency')
//    console.log({ request, code })
//  }
//}
//
//CustomDependency.Template = class CustomDependencyTemplate extends (
//  ModuleDependency.Template
//) {
//  apply(dependency, source, templateContext) {
//    console.log('template')
//    console.log({ dependency, source, templateContext })
//  }
//}

class CustomDependency extends ConstDependency {
  constructor(request, code) {
    super();
    console.log('dep');
  }
}

CustomDependency.Template = class CustomDependencyTemplate extends (
  ConstDependency.Template
) {
  apply(dependency, source, templateContext) {
    console.log('template');
    source.insert(0, 'console.log("wtf");');
  }
};

function ObserveHookCalls() {
  this.PLUGIN_NAME = 'ObserveHookCalls';
}

ObserveHookCalls.prototype.apply = function (compiler) {
  // Hook in all the hooks and observe the order of calls.
  const { PLUGIN_NAME } = this;

  Object.entries(compiler.hooks).forEach(([key, value]) => {
    value.tap(PLUGIN_NAME, (...args) => {
      const hooks = args[0]?.hooks;
      if (hooks) {
        //console.log(key, ':')
        //Object.entries(hooks).forEach(([k, v]) => {
        //  console.log('-- ', k, v.for, v.tap)
        //})
      } else {
        //console.log(key, args)
      }
    });
  });

  // Test if i can do something here...
  // compiler.hooks.normalModuleFactory.tap(PLUGIN_NAME, nmf => {
  //   nmf.hooks.parser.for('javascript/auto').tap(PLUGIN_NAME, parser => {
  //     parser.hooks.program.tap(PLUGIN_NAME, (ast, comments) => {
  //       console.log('yayyyy')// Ok Runs once per module ...
  //     })
  //   })
  // })

  compiler.hooks.compilation.tap(
    PLUGIN_NAME,
    (compilation, { normalModuleFactory }) => {
      console.log('set custom dependency template');
      compilation.dependencyTemplates.set(
        CustomDependency,
        new CustomDependency.Template()
      );
      const { runtimeTemplate } = compilation;
      console.log({ normalModuleFactory, runtimeTemplate });
    }
  );

  compiler.hooks.normalModuleFactory.tap(PLUGIN_NAME, (nmf) => {
    function handler(parser) {
      parser.hooks.program.tap(PLUGIN_NAME, (ast, comments) => {
        // Here I should be able to somehow from the AST figure out the import paths
        // and I could set the dependency and pass the dependency some information that it requires

        traverse(parse(astring.generate(ast), { sourceType: 'module' }), {
          CallExpression(nodePath) {
            // What about other imports? How many do I have to handle?
            if (t.isIdentifier(nodePath.node.callee, { name: 'require' })) {
              if (nodePath.node.arguments.length > 0) {
                const requirePath = nodePath.node.arguments[0].value;
                const { context, resource, request } = parser.state.module;

                const { dir, base } = path.parse(requirePath);
                const tenant = 'one';
                const dynamicImportPath =
                  dir + path.sep + path.join('tenant', '${tenant}', base);

                // A few problems with this approach:
                // What is the user supposed to do with the imported module? How can we give him the control?
                // What do we do with the import he wrote?
                // The variable we are using pollutes user code space.
                // It is possible that webpack doesn't compile this dynamic import. Dynamic import compiles properly when I manually add it to index.js file.
                // More work to do... Duh!

                const code = `
                ;(function() {
                  const tenant = null;
                  if (tenant) {
                    console.log(\`${dynamicImportPath}\`);
                    import(\`${dynamicImportPath}\`).then(module => onModuleLoaded(module.default));
                  } else {
                    import('${requirePath}').then(module => onModuleLoaded(module.default));
                  }
                })();`;

                console.log({ code });
                console.log({ dynamicImportPath });
                // Now I've gotta figure out a way to provide the code to the plugin.
                // I don't know if the timing will work.
                // Then I've gotta figure out how to provide the value of the tenant to the plugin from user perspective.
                const overridablePath = path.join(
                  context,
                  path.dirname(requirePath),
                  'tenant'
                );
                console.log({
                  overridablePath,
                  requirePath,
                  context,
                  dynamicImportPath,
                });

                // I believe that adding my custom dependency messes up a module badly
                // It is good thing because it means i'm making progress because now i can alter module significantly
                // parser.state.module.addDependency(new CustomDependency(request, code));
                //
                // Modules aren't resolved now... Maybe cus I add dependency conditionally? No idea...
                // if (fs.existsSync(overridablePath)) {
                //   console.log('add dependency', { resource });
                //   parser.state.module.addDependency(new CustomDependency(code));
                // }
              } else {
                // Not sure if we should report require call without args
              }
            }
          },
        });
        // console.log(babel.ast, generate(babel.ast).code)
        //        console.log('parser.state.module', parser.state.module.dependencies)
      });
    }

    nmf.hooks.parser.for(JAVASCRIPT_MODULE_TYPE_AUTO).tap(PLUGIN_NAME, handler);
  });

  compiler.hooks.compilation.tap(PLUGIN_NAME, (compilation) => {
    // usage, purpose, use cases of these two
    // compilation.dependencyFactories
    // compilation.dependencyTemplates

    compilation.hooks.succeedModule.tap(PLUGIN_NAME, (module) => {
      // console.log('module.resource', module.resource, module.dependencies)
    });

    const hooks =
      compiler.webpack.javascript.JavascriptModulesPlugin.getCompilationHooks(
        compilation
      );
    // These aren't the same.
    // for(const key in hooks) console.log(key);
    // console.log('------------------')
    // for(const key in compilation.hooks) console.log(key);
    hooks.chunkHash.tap(PLUGIN_NAME, (chunk, hash) => {
      // console.log({ hash, chunk })
      // Not sure why does TerserPlugin call these two. Not sure how do they affect hash or whatever...
      // hash.update(PLUGIN_NAME);
      // hash.update(
    });

    // Research code block:
    // compilation.hooks.buildModule.tap(PLUGIN_NAME, (module) => {
    //   Registering the hook here breaks the build.
    //
    //   if (buildInfo.assets) {
    //   TypeError: Cannot read properties of undefined (reading 'assets')
    //
    //   module.parser.hooks.program.tap(PLUGIN_NAME, (ast, comments) => {
    //   })
    // })

    compilation.hooks.processAssets.tapPromise(
      {
        name: PLUGIN_NAME,
        stage: compiler.webpack.Compilation.PROCESS_ASSETS_STAGE_OPTIMIZE_SIZE,
        additionalAssets: true,
      },
      async (assets) => {
        const cache = compilation.getCache(PLUGIN_NAME);
        // WTF do I do with cache?
        // console.log({ cache });
        const assetsToMinify = await Promise.all(
          Object.keys(assets)
            .filter((name) => {
              const asset = compilation.getAsset(name);
              // console.log({asset})
              return true;
            })
            .map(async (name) => {
              // First time seeing these ideas in my life...
              const asset = compilation.getAsset(name);
              const eTag = cache.getLazyHashedEtag(asset.source);
              const cacheItem = cache.getItemCache(name, eTag);
              const output = await cacheItem.getPromise();

              // Same asset as above...
              // console.log({asset, eTag, cacheItem, output})

              return {
                name,
                info: asset.info,
                inputSource: asset.source,
                output,
                cacheItem,
              };
            })
        );

        for (const asset of assetsToMinify) {
          const { name, inputSource, info, cacheItem } = asset;
          const { source, map } = inputSource.sourceAndMap();
          // console.log(serialize({ name, input: source, inputSourceMap: map }));
        }
        // const {source: sourceFromInputSource, map} = assetsToMinify[0].inputSource.sourceAndMap()
        // const input = sourceFromInputSource
        // console.log({ assetsToMinify, sourceFromInputSource, map, 'input.toString()': input.toString()})
        // console.log('serialize', serialize({  }))

        // The idea that terser plugin uses is once the assets are processed it serializes the non-serializable
        // javascript code and passes the string of the javascript code to terser minify function which
        // returns it and i guess it returns it to webpack somehow... and that code... works? Or whatever...
        // not sure...
      }
    );
  });
};

// (I don't know if this is going to work, but)
// If I can't get this to work, then I could say that an overridable import must obide by two conditions:
// It must be already a dynamic import.
// There must be a directory next to it.

// If WhatTheFuck extends Dependency, moduleGraph.getModule(dep) CAN NOT find
// the dependency WhatTheFuck
//
// If WhatTheFuck extends ModuleDependency, moduleGraph.getModule(dep) CAN find
// the module for dependency WhatTheFuck
class WhatTheFuck extends ModuleDependency {
  constructor(request) {
    // Is it because of a request?
    // That is the only difference I saw...
    // If a request is not provided, module graph won't be able to find module
    // related to this dependency...
    super(request);
    // console.log({ request });
  }

  // override getResourceIdentifier to see if the behavior still occurs
  // overriding it makes behavior funny... gosh:)

  get type() {
    console.log('WhatTheFuck__type()');
    return 'what the fuck';
  }

  get category() {
    console.log('WhatTheFuck__category()');
    return 'esm';
  }
}

WhatTheFuck.Template = class WhatTheFuckTemplate
  // Research on why do I have to inherit this class...
  extends ModuleDependency.Template
{
  apply(dep, source, { moduleGraph, chunkGraph, runtimeTemplate }) {
    // const module = moduleGraph.getModule(dep);
    // if (module) {
    //   console.log('-- moduleGraph.getModule(dep) found --')
    // } else {
    //   console.log('-- moduleGraph.getModule(dep) not found --')
    // }
  }
};

class OhMyGod {
  plugin = 'OhMyGod';
  apply(compiler) {
    // Use parser hooks like webpack does to see what the heck to do...
    const { plugin } = this;

    compiler.hooks.compilation.tap(
      plugin,
      (compilation, { normalModuleFactory }) => {
        // dependencyFactories and dependencyTemplates is a pattern used by
        // webpack internally in plugins such as ImportParser,
        // CommonjsRequireParser, and more... Why it works I don't know as I'd
        // need a deeper understanding of webpack.
        //
        // Also adding dependencyFactories made it run before the
        // ImportDependency.Template
        compilation.dependencyFactories.set(WhatTheFuck, normalModuleFactory);
        compilation.dependencyTemplates.set(
          WhatTheFuck,
          new WhatTheFuck.Template()
        );

        // Runs before ImportParserPlugin applied by webpack internally.
        normalModuleFactory.hooks.parser
          .for('javascript/auto')
          .tap(plugin, (parser, parserOptions) => {
            parser.hooks.importCall.tap(plugin, (expr) => {
              const param = parser.evaluateExpression(expr.source);
              if (param.isString()) {
                parser.state.current.addDependency(
                  new WhatTheFuck(param.string)
                );
              } else {
                // No idea... I saw this kind of code in ImportParserPlugin
                // I now understand it's for segmented imports and I've no idea
                // how to handle them.
              }

              // console.log({ expr })
              // console.log(astring.generate(expr))
              // console.log(acorn.parse(astring.generate(expr), { sourceType: 'module' }), '---')
              // console.log(acorn.parse(`import('./src/wtf')`, { sourceType: 'module' }))
              //
              // JavascriptParser._parse gives us consistent output with the expr that we receive here
              // the problem is in which way are we allowed to alter the expr parameter of the importCall hook
              // i am not entirely sure how are we allowed to alter the ast... because i'm certain webpack has
              // expectations on the state of the ast and we have to abide by those expectations...
              // console.log('JsParser',
              //   JavascriptParser._parse(`import('./src/wtf')`, { sourceType: 'module' }).body[0].expression
              // )

              // So this is possible... Perhaps... I can replace a whole require AST as an import ast
              // expr.source.value = './src/wtf'
              // expr.source.raw = "'./src/wtf'"
              // const { moduleGraph } = compilation;
              // compilation.rebuildModule(parser.state.current, (err, result) => {
              //   if (err) {
              //     console.log({ err })
              //     return;
              //   }
              //   console.log('module_built_again', { result })
              // })
            });
          });

        // compilation.hooks.finishModules.tap(plugin, (modules) => {
        //   console.log('finishModules')
        //   modules.forEach(module => {
        //     console.log(module.identifier(), module.dependencies)
        //   })
        // })

        // normalModuleFactory.hooks.beforeResolve.tap(plugin, (module) => {
        //   console.log('before resolve');
        // });
        // normalModuleFactory.hooks.resolve.tap(plugin, module => {
        //   console.log('resolve');
        // })

        // compilation.hooks.processAssets.tap({
        //   name: plugin,
        //   stage: Compilation.PROCESS_ASSETS_STAGE_OPTIMIZE
        // }, (assets) => {
        //   console.log('assets', assets)
        // })

        // I am looking for a way to insert the code into module before parsing occurs...

        // const { moduleGraph, dependencyTemplates } = compilation;

        // compilation.hooks.buildModule.tap(plugin, (module) => {
        //   // Template doesn't get called if i add it at this stage, but it gets
        //   // called if i add it at parsing stage... why the fuck?
        //   // console.log('module', module.request);
        // });

        // compilation.hooks.finishModules.tap(plugin, (modules) => {
        //   for (const module of modules) {
        //     for (const connection of moduleGraph.getOutgoingConnections(
        //       module
        //     )) {
        //       const ctor = connection.dependency.constructor;
        //     }
        //   }
        // });

        // Perhaps I should explore more paths if there is some possibility to
        // edit the code of a module, however if there's no import already, we
        // don't get the module's source code here...
        // const handler = (parser, parserOptions) => {
        //   parser.hooks.importCall.tap(plugin, (expr) => {
        //     // const param = parser.evaluateExpression(expr.source)
        //     // console.log(parser.state.current.request)
        //     // parser.state.current.addDependency(new WhatTheFuck(parser.state.current.request))
        //     // And therefore the current module should be resolved asynchronously?
        //     // Somehow? That's how they do it in webpack within:
        //     // ImportParserPlugin
        //     // It is possible to add AsyncDependencyBlock to parser.state.current.addBlock()
        //     // might be possible to do something at parser.hooks.evaluate before
        //     // it actually does stuff, maybe? not sure...
        //   });
        // };

        // normalModuleFactory.hooks.parser
        //   .for(JAVASCRIPT_MODULE_TYPE_DYNAMIC)
        //   .tap(plugin, handler);
        // normalModuleFactory.hooks.parser
        //   .for(JAVASCRIPT_MODULE_TYPE_ESM)
        //   .tap(plugin, handler);
        // normalModuleFactory.hooks.parser
        //   .for(JAVASCRIPT_MODULE_TYPE_AUTO)
        //   .tap(plugin, handler);
      }
    );
  }
}

module.exports = {
  entry: './index.js',
  target: 'node',
  externals: [nodeExternals()],
  output: {
    path: path.resolve(__dirname, 'dist', process.env.TENANT),
    filename: 'build.js',
  },
  devtool: false, // Readable output.
  plugins: [
    {
      apply(compiler) {
        // importSpecifier runs for `import` statement...:( jesus
        // const pluginName = 'PluginNameLolz'
        // compiler.hooks.normalModuleFactory.tap(pluginName, normalModuleFactory => {
        //   normalModuleFactory.hooks.parser.for('javascript/auto').tap(pluginName, parser => {
        //     parser.hooks.importSpecifier.tap(pluginName, (...args) => {
        //       console.log('importSpecifier')
        //     })
        //     parser.hooks.call.for('require').tap(pluginName, expression => {
        //       console.log('require', expression)
        //     })
        //     console.log('parser')
        //   })
        // })
      },
    },
    new Tenant({ tenant: process.env.TENANT }),
    // new Something(),
    // new ObserveHookCalls(),
    // new OhMyGod(),
  ],
};
