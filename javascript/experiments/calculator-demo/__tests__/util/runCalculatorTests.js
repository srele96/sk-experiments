function runCalculatorTests(calculator, test) {
  console.log('----');
  console.log('TEST: ' + test);
  console.log('1 + 1 = ' + calculator.add(1, 1));
  console.log('5 - 3 = ' + calculator.subtract(5, 3));
  console.log('5 * 3 = ' + calculator.multiply(5, 3));
  console.log('10 / 5 = ' + calculator.divide(10, 5));
}

module.exports.runCalculatorTests = runCalculatorTests;
