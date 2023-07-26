# Generate Elements

Generate an object of elements from one or more arrays.

## Fun story about documentation

I wrote a 50 lines of code library over 8 months ago and decided to use it. I wrote no examples, documentation, etc... I assumed it was intuitive to use it.

Guess what, it was not. I forgot and I had to look at code I previously used to learn how to use it. Thankfully because I wrote it I only required a few minutes to understand what to do.

Always document everything that might be forgotten, because it will be forgotten.

## Documentation

Map multiple properties to each element and create html elements.

```js
const elements = FlexosGenerateElements.generateElements({
  data: {
    innerHTML: ['Title', 'First Paragraph', 'Second Paragraph'],
    type: ['h1', 'p', 'p'],
    'aria-label': ['Title', 'First Paragraph', 'Second Paragraph'],
  },
});

Object.entries(elements).forEach(([key, value]) => {
  const element = document.createElement(value.type);
  element.innerHTML = value.innerHTML;
  element.setAttribute('aria-label', value['aria-label']);

  document.body.appendChild(element);
});
```

Map angles and create elements that use them.

```js
const YELLOW = 'yellow';
const RED = 'red';
const COLOR = { YELLOW, RED };

const elements = FlexosGenerateElements.generateElements({
  data: {
    angleDegree: [0, 15, 30],
  },
  // Set distinct color only for the specific key.
  each: (key, value) => {
    // Keys are always strings.
    const FIRST_KEY = '0';

    return {
      key,
      value: {
        ...value,
        color: key === FIRST_KEY ? COLOR.YELLOW : COLOR.RED,
      },
    };
  },
});

Object.entries(elements).forEach(([key, value]) => {
  const element = document.createElement('div');

  element.style.display = 'inline-block';
  element.style.width = '100px';
  element.style.height = '100px';
  element.style.backgroundColor = value.color;
  element.style.transformOrigin = 'center bottom';
  element.style.transform = `rotate(${value.angleDegree}deg)`;

  document.getElementById('rotate-main-element').appendChild(element);
});
```

Swap two elements using their keys and the `modify` option.

```js
// Keys are treated as strings.
const FIRST_KEY = '0';
const SECOND_KEY = '1';

const beforeModify = FlexosGenerateElements.generateElements({
  data: {
    degree: [0, 15, 30],
    xOffset: [0, 100, 200],
  },
});

const afterModify = FlexosGenerateElements.generateElements({
  data: {
    degree: [0, 15, 30],
    xOffset: [0, 100, 200],
  },
  modify: {
    keyA: FIRST_KEY,
    keyB: SECOND_KEY,
    // May be used to swap values, modify keys, etc...
    cb: (valA, valB) => {
      // Swap degree of valA and valB.
      return {
        [FIRST_KEY]: {
          ...valA,
          degree: valB.degree,
        },
        [SECOND_KEY]: {
          ...valB,
          degree: valA.degree,
        },
      };
    },
  },
});

document.getElementById('before-modify').innerHTML = JSON.stringify(
  beforeModify,
  null,
  2
);

document.getElementById('after-modify').innerHTML = JSON.stringify(
  afterModify,
  null,
  2
);
```

Output:

Before modify:

```json
{
  "0": { "degree": 0, "xOffset": 0 },
  "1": { "degree": 15, "xOffset": 100 },
  "2": { "degree": 30, "xOffset": 200 }
}
```

After modify:

```json
{
  "0": { "degree": 15, "xOffset": 0 },
  "1": { "degree": 0, "xOffset": 100 },
  "2": { "degree": 30, "xOffset": 200 }
}
```

For more examples and behavior see [`index.spec.js`](./index.spec.js).
