const calculator = require('../dist/calculator.development');
const {
  add,
  subtract,
  multiply,
  divide,
} = require('../dist/calculator.development');
const { runCalculatorTests } = require('./util/runCalculatorTests');

runCalculatorTests(calculator, 'default export - development build');
runCalculatorTests(
  { add, subtract, multiply, divide },
  'named export - development build'
);
