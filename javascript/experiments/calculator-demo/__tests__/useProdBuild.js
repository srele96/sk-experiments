const calculator = require('../dist/calculator.production');
const {
  add,
  subtract,
  multiply,
  divide,
} = require('../dist/calculator.production');
const { runCalculatorTests } = require('./util/runCalculatorTests');

runCalculatorTests(calculator, 'default export - production build');
runCalculatorTests(
  { add, subtract, multiply, divide },
  'named export - production build'
);
