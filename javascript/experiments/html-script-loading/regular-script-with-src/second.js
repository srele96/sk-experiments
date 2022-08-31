console.log('second.js');
// this loop should log value after the loop in first.js
for (let i = 0; i < 2; i++) {
  console.log({ 'second.js': i });
}
