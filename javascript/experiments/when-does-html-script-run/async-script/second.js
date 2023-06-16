console.log('second.js');
// if this script is loaded before the first.js
// the following value won't be declared and initialized
console.log({ possibly_non_declared_variable });
