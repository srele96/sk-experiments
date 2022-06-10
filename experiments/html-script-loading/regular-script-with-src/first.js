console.log('first.js');
// does everything in the script load synchronously
// if the for loop in the first.js is executed before
// the log and for loop in second.js
// then everything in the script loads synchronously
for (let i = 0; i < 2; i++) {
  console.log({ 'first.js': i });
}
