const { getHeapNumbers, push, pop, peek } = require('../min_heap');

function makeHeapEmpty() {
  while (getHeapNumbers().length > 0) {
    pop();
  }
}

describe('min_heap', () => {
  beforeEach(() => {
    makeHeapEmpty();
  });

  test('should push one number in the heap correctly', () => {
    push(0);
    const validHeapNumbers = [0];
    expect(getHeapNumbers()).toEqual(validHeapNumbers);
  });

  test('should push two numbers in the heap correctly', () => {
    push(5);
    push(2);

    const validHeapNumbers = [2, 5];

    expect(getHeapNumbers()).toEqual(validHeapNumbers);
  });

  test('should push five numbers in the heap correctly', () => {
    push(5);
    push(2);
    push(-3);
    push(10);
    push(-5);

    const validHeapNumbers = [-5, -3, 2, 10, 5];

    expect(getHeapNumbers()).toEqual(validHeapNumbers);
  });

  test('should peek at top element without removing it', () => {
    push(5);
    push(-5);

    expect(peek()).toBe(-5);
  });

  test('should pop top element correctly', () => {
    push(5);
    push(-5);
    push(-10);

    expect(pop()).toBe(-10);
  });

  test('should return undefined when we pop empty heap', () => {
    expect(pop()).toBe(undefined);
  });
});
