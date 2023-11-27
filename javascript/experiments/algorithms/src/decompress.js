/*
 * Problem source:
 * https://techdevguide.withgoogle.com/resources/former-interview-question-compression-and-decompression/#!
 *
 * I trust that Google is nice and won't make the link above obsolete.
 **/

const isDigit = (str) => Number.isFinite(Number.parseInt(str));

function Token(string = '', number = null, decompressible = false) {
  this.string = string;
  this.number = number;
  this.decompressible = decompressible;
}

function tokenize(input) {
  let result = [];
  let i = 0;
  while (i != input.length) {
    if (isDigit(input.charAt(i))) {
      let digits = '';
      // collect digits and use i to stay within O(n) time complexity
      while (isDigit(input.charAt(i))) {
        digits += input.charAt(i);
        ++i;
      }
      const number = Number.parseInt(digits);
      // skip the first opening parentheses because we only want to collect
      // the characters between them
      ++i;
      let openedParentheses = 1;
      let isInnerStringDecompressible = false;
      let characters = '';
      // parse until closing parentheses
      while (openedParentheses > 0) {
        if (input.charAt(i) === '[') {
          ++openedParentheses;
          isInnerStringDecompressible = true;
        } else if (input.charAt(i) === ']') {
          --openedParentheses;
        }
        if (openedParentheses !== 0) {
          // at the moment opened parentheses are 0, it means we have found
          // the closing parentheses that we were looking for and content
          // between the parentheses has been parsed so we exclude it as well
          // as we did exclude the first one
          characters += input.charAt(i);
        }
        ++i;
      }
      result.push(new Token(characters, number, isInnerStringDecompressible));
    } else {
      let characters = '';
      // parse until first digit which means next token or end of input because
      // we may receive only a string without following digits
      while (!isDigit(input.charAt(i)) && i !== input.length) {
        characters += input.charAt(i);
        ++i;
      }
      // Based on the problem statement the string may only contain
      // lowercase english characters.
      result.push(new Token(characters));
    }
  }
  return result;
}

function decompress(input) {
  let result = '';
  for (const token of tokenize(input)) {
    const maybeDecompressed = token.decompressible
      ? decompress(token.string)
      : token.string;
    if (isDigit(token.number)) {
      // repeat the string the number of times
      for (let i = 0; i !== token.number; ++i) {
        result += maybeDecompressed;
      }
    } else {
      result += maybeDecompressed;
    }
  }
  return result;
}

module.exports.decompress = decompress;
