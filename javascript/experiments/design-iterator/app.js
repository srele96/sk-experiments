function createIterator() {
  return (() => {
    const listOneKey = 'one';
    const listOneNumber = 0;
    const listTwoKey = 'two';
    const listTwoNumber = 1;
    const listThreeKey = 'three';
    const listThreeNumber = 2;
    const initialIndex = 0;

    function createAccessor({ key, number, pointer }) {
      return {
        key,
        number,
        pointer,
        next() {
          ++this.pointer;
        },
      };
    }

    const access = {
      [listOneKey]: createAccessor({
        key: listOneKey,
        number: listOneNumber,
        pointer: initialIndex,
      }),
      [listTwoKey]: createAccessor({
        key: listTwoKey,
        number: listTwoNumber,
        pointer: initialIndex,
      }),
      [listThreeKey]: createAccessor({
        key: listThreeKey,
        number: listThreeNumber,
        pointer: initialIndex,
      }),
    };

    const isEven = (value) => value % 2 === 0;
    const isOdd = (value) => value % 2 === 1;

    return (...lists) => {
      // Abstraction wrapper so the loop doesn't know how we access elements
      // and what does it mean to be a valid value.
      function createWrapper(__value, __accessorKey) {
        return {
          __value,
          __accessorKey,
          isValid() {
            // Lists 1 and 3 accept only even numbers.
            const isListOne = this.__accessorKey === listOneKey;
            const isListThree = this.__accessorKey === listThreeKey;
            if (isListOne || isListThree) {
              return isEven(this.__value);
            }
            // List 2 accepts only odd numbers.
            const isListTwo = this.__accessorKey === listTwoKey;
            if (isListTwo) {
              return isOdd(this.__value);
            }
          },
          pointNext() {
            access[this.__accessorKey].next();
          },
          value() {
            return this.__value;
          },
        };
      }

      function createElement({ accessorNumber, accessorPointer, accessorKey }) {
        return {
          hasNext: lists[accessorNumber].length !== accessorPointer,
          list: lists[accessorNumber],
          accessorKey,
        };
      }

      const handler = {
        // Set up next set of elements and return state whether we have any
        // number accessible.
        next() {
          // Filter out the elements that would cause list overflow and solve
          // the problem of comparison of variadic amount of elements.
          this.__elements = [
            createElement({
              accessorNumber: access.one.number,
              accessorPointer: access.one.pointer,
              accessorKey: access.one.key,
            }),
            createElement({
              accessorNumber: access.two.number,
              accessorPointer: access.two.pointer,
              accessorKey: access.two.key,
            }),
            createElement({
              accessorNumber: access.three.number,
              accessorPointer: access.three.pointer,
              accessorKey: access.three.key,
            }),
          ].filter((list) => list.hasNext);

          const hasNext = this.__elements.length !== 0;
          return hasNext;
        },
        // Pick the smallest value out of all currently pointed values
        // and return wrapper that holds it.
        // Depends on invariant that next() holds:
        //   elements are lists to which accessor pointer points to element
        //   within list's bounds.
        smallest() {
          let smallest = createWrapper(null);
          // Smallest element comparison is search for smallest value
          // the pointer points to.
          this.__elements.forEach(({ list, accessorKey }) => {
            let currentNumber = list[access[accessorKey].pointer];
            if (smallest.value()) {
              if (currentNumber < smallest.value()) {
                // Found smaller value.
                smallest = createWrapper(currentNumber, accessorKey);
              }
            } else {
              // Initialize
              smallest = createWrapper(currentNumber, accessorKey);
            }
          });
          return smallest;
        },
      };

      // Post implementation impressions:
      //
      // I designed this loop with abstraction in mind. I wanted to design it
      // so the loop doesn't know:
      //  - what it means to have next element
      //  - how the smallest element is found
      //  - what it means to point to next element
      //  - what it means for element to be valid
      //  - hide implementation of value
      //
      // At the end of implementation the decision I made looks costly because
      // both handler and current require (subjectively) quite a bit of code
      // to hide those details.
      //
      // One thing I dislike in particular is how I had to exchange information
      // between handler and current entity such as from where the element was
      // accessed.
      // However, I really liked the idea of having look that depends on
      // abstractions and making it expressive.
      while (handler.next()) {
        const current = handler.smallest();
        // I wasn't entirely sure which entity was supposed to be owner of the
        // operation to point to the next element. Both current and handler
        // appear as weak entities to own it.
        current.pointNext();
        if (current.isValid()) return current.value();
      }
    };
  })();
}

// ----------------------------------------------------------------------------
// A better approach would be to have tests, but I couldn't use them in an
// environment I wrote this code originally.
// ----------------------------------------------------------------------------

// Testing helper to avoid repetitive iterator dumping.
function dumpIterator(lists, getNext) {
  let next = getNext(...lists);
  while (next) {
    console.log(next);
    next = getNext(...lists);
  }
}

function printOneLastValidNumber() {
  const getNext = createIterator();
  let args = [
    [1, 5, 9, 13, 2], // New Line.
    [2, 4, 6, 8, 10], // New Line.
    [3, 7, 11], // New Line.
  ];
  dumpIterator(args, getNext);
}

function printAllValid() {
  const getNext = createIterator();
  let args = [
    [2, 6, 10, 14], // New Line.
    [3, 7, 11, 15], // New Line.
    [4, 8, 12, 16], // New Line.
  ];
  dumpIterator(args, getNext);
}

function printAll() {
  const getNext = createIterator();
  let args = [
    [1, 8, 15, 16, 35], // New Line.
    [2, 7, 12, 63], // New Line.
    [10, 13, 14, 42], // New Line.
  ];
  dumpIterator(args, getNext);
}

const separator = '-------------';

printOneLastValidNumber();
console.log(separator);
printAllValid();
console.log(separator);
printAll();
