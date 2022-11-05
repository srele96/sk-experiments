function produceSequence({ initialValue, changeSubsequentBy, length }) {
  invariant.validNumbers(initialValue, length);
  invariant.validNumbers(...changeSubsequentBy);
  invariant.validArray(changeSubsequentBy);
  invariant.lengthEqualOrLess(changeSubsequentBy, length);

  let initialValue_DontModifyArgument = initialValue;
  let changeSubsequentBy_DontModifyArgument = changeSubsequentBy.slice();
  let change = 0;

  const sequence = new Array(length);

  for (let i = 0; i != length; ++i) {
    initialValue_DontModifyArgument += change;
    sequence[i] = initialValue_DontModifyArgument;

    if (changeSubsequentBy_DontModifyArgument.length > 0) {
      change = changeSubsequentBy_DontModifyArgument.shift();
    }
  }

  return sequence;
}
