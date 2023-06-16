// Use IIFE to prevent global name clashes.
(() => {
  const { StrictMode, createElement: e, useState, Fragment } = React;
  const { createRoot } = ReactDOM;

  function InputWithLabel({ id, value, onChange }) {
    return e(
      'label',
      { htmlFor: id },
      `${id}: `,
      e('input', {
        style: { display: 'block' },
        id,
        name: id,
        type: 'number',
        value,
        onChange: (event) => {
          const value = Number(event.target.value);
          onChange(value);
        },
      })
    );
  }

  function Elements({ elements, mainElementValue }) {
    const sharedStyle = {
      width: '30px',
      height: '30px',
      display: 'flex',
      flexDirection: 'row',
      justifyContent: 'center',
      alignItems: 'center',
      fontSize: '25px',
      fontWeight: 'bold',
    };

    return e(
      'ul',
      null,
      elements.map(({ order }) => {
        return e(
          'li',
          { key: order },
          e(
            'div',
            {
              style:
                order === mainElementValue
                  ? { ...sharedStyle, backgroundColor: 'red' }
                  : {
                      ...sharedStyle,
                      backgroundColor: 'black',
                      color: 'white',
                    },
            },
            order
          )
        );
      })
    );
  }

  function App() {
    const defaultLength = 11;
    const [length, setLength] = useState(defaultLength);
    const defaultMainElement = 6;
    const [mainElement, setMainElement] = useState(defaultMainElement);

    function saveLength(newLength) {
      if (newLength >= mainElement) {
        setLength(newLength);
      }
    }

    function saveMainElement(newMainElement) {
      if (newMainElement < 1) {
        setMainElement(length);
      } else if (newMainElement > length) {
        setMainElement(1);
      } else {
        setMainElement(newMainElement);
      }
    }

    const getElements = FlexosElements.get_elements({ length });
    const elements = getElements(mainElement);
    const mainElementValue = 0;

    return e(
      'div',
      null,
      e('h1', null, 'Change numbers to see stuff happen'),
      e(
        'div',
        null,
        e(InputWithLabel, {
          id: 'length',
          value: length,
          onChange: saveLength,
        })
      ),
      e(
        'div',
        null,
        e(InputWithLabel, {
          id: 'main-element',
          value: mainElement,
          onChange: saveMainElement,
        })
      ),
      e(Elements, { elements, mainElementValue })
    );
  }

  function renderApp() {
    const id = 'root';
    const domRoot = document.getElementById(id);
    const root = createRoot(domRoot);

    root.render(e(StrictMode, null, e(App)));
  }

  renderApp();
})();
