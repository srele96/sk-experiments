// Our plugin expects a variable with this very name in order to work. A
// downside is that this variable is reserved by our plugin and user is limited
// to be unable to use it in his code out of his own free will.
// However it's also a benefit that user can use types and various checks on
// his config as well.
const __OVERRIDE__CONFIG__ = {
  importPath: './src/mod',
};

// Our loader expects `__on_module__` name because it will pass it to dynamic
// import
function __on_module__(module) {
  const mod = module.default ?? module;
  console.log(`mod = ${mod()}`);
}

function __on_error__(error) {
  console.log('error loading module');
}
