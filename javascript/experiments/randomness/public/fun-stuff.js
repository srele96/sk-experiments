(() => {
  'use strict';

  const { createElement: e, StrictMode, useEffect, useState } = React;
  const { createRoot } = ReactDOM;

  function createStorageKey() {
    const pageTitle = 'page-title';
    const pageDescription = 'page-description';
    const pageStyle = 'page-style';

    const storageKey = { pageTitle, pageDescription, pageStyle };

    return storageKey;
  }

  function App() {
    const storageKey = createStorageKey();

    // --------------------------------------------------------------------

    const pageTitleInputId = 'page-title';
    const pageTitleInputLabel = 'Page title';
    const initialPageTitle = 'Hello React World!';
    const defaultPageTitle =
      localStorage.getItem(storageKey.pageTitle) ?? initialPageTitle;
    const [pageTitle, setPageTitle] = useState(defaultPageTitle);

    function savePageTitle(event) {
      setPageTitle(event.target.value);
    }

    // --------------------------------------------------------------------

    const pageDescriptionInputId = 'page-description';
    const pageDescriptionInputLabel = 'Page description';
    const initialPageDescription = 'This is my page and it rocks!';
    const defaultPageDescription =
      localStorage.getItem(storageKey.pageDescription) ??
      initialPageDescription;
    const [pageDescription, setPageDescription] = useState(
      defaultPageDescription
    );

    function savePageDescription(event) {
      setPageDescription(event.target.value);
    }

    // --------------------------------------------------------------------

    const pageStyleInputId = 'page-style';
    const pageStyleInputLabel = 'Page style';
    const initialPageStyle = '';
    const defaultPageStyle =
      localStorage.getItem(storageKey.pageStyle) ?? initialPageStyle;
    const [pageStyle, setPageStyle] = useState(defaultPageStyle);

    function savePageStyle(event) {
      setPageStyle(event.target.value);
    }

    // --------------------------------------------------------------------

    useEffect(() => {
      const id = 'head-title';
      const title = document.getElementById(id);
      title.innerHTML = pageTitle;
    }, [pageTitle]);

    // --------------------------------------------------------------------

    useEffect(() => {
      const meta = document.createElement('meta');
      meta.name = 'description';
      meta.content = pageDescription;
      document.head.appendChild(meta);

      return () => {
        document.head.removeChild(meta);
      };
    }, [pageDescription]);

    // --------------------------------------------------------------------

    useEffect(() => {
      const style = document.createElement('style');
      style.innerHTML = pageStyle;
      document.head.appendChild(style);

      return () => {
        document.head.removeChild(style);
      };
    }, [pageStyle]);

    // --------------------------------------------------------------------

    useEffect(() => {
      localStorage.setItem(storageKey.pageTitle, pageTitle);
      localStorage.setItem(storageKey.pageDescription, pageDescription);
      localStorage.setItem(storageKey.pageStyle, pageStyle);
    }, [pageTitle, pageDescription, pageStyle]);

    // --------------------------------------------------------------------

    const rowContent = 'row';

    // --------------------------------------------------------------------

    return e(
      'main',
      null,
      e('h1', null, 'Hello World!'),
      e(
        'label',
        { htmlFor: pageTitleInputId, className: rowContent },
        pageTitleInputLabel,
        e('textarea', {
          id: pageTitleInputId,
          onChange: savePageTitle,
          value: pageTitle,
        })
      ),
      e(
        'label',
        { htmlFor: pageDescriptionInputId, className: rowContent },
        pageDescriptionInputLabel,
        e('textarea', {
          id: pageDescriptionInputId,
          onChange: savePageDescription,
          value: pageDescription,
        })
      ),
      e(
        'label',
        { htmlFor: pageStyleInputId, className: rowContent },
        pageStyleInputLabel,
        e('textarea', {
          id: pageStyleInputId,
          onChange: savePageStyle,
          value: pageStyle,
        })
      )
    );
  }

  function renderApp() {
    const id = '__root__';
    const domRoot = document.getElementById(id);
    const reactRoot = createRoot(domRoot);

    reactRoot.render(e(StrictMode, null, e(App)));
  }

  renderApp();
})();

(() => {
  'use strict';

  const { createElement: e, useEffect, useState } = React;
  const { createRoot } = ReactDOM;
  const { get_elements } = FlexosElements;

  const length = 5;
  const createSequence = get_elements({
    length,
    callback: (element) => {
      return {
        ...element,
        // Make each non-main element 10% visible
        xOffset: element.order * 10,
        // Show first main element and the others sequentially behind
        zIndex: element.order < 0 ? element.order : -element.order,
        // Make subsequent elements by .1 smaller
        scale: 1 - Math.abs(element.order) / 10,
      };
    },
  });

  function App() {
    const initialMailElement = 1;
    const [mainElement, setMainElement] = useState(initialMailElement);

    useEffect(() => {
      const styles = `
        .card {
          background-color: purple;
          transition: .1s ease-in-out;
        }
        .card:hover {
          background-color: yellow;
        }
      `;
      const style = document.createElement('style');

      style.innerHTML = styles;
      document.head.appendChild(style);
    }, []);

    return e(
      'main',
      null,
      e('h1', null, 'Hello Root-Two'),
      e(
        'ul',
        {
          style: {
            position: 'relative',
            width: '300px',
            height: '300px',
            // The child elements have negative zIndex so this one keeps
            // them above the document so they are hoverable.
            zIndex: 0,
          },
        },
        createSequence(mainElement).map(
          ({ order, xOffset, zIndex, scale }, i) => {
            return e(
              'li',
              {
                key: order,
                className: 'card',
                // Use index to set main element. Main element starts
                // from 1, index starts from 0.
                onClick: () => setMainElement(i + 1),
                style: {
                  position: 'absolute',
                  width: '100%',
                  height: '100%',
                  display: 'flex',
                  alignItems: 'center',
                  justifyContent: 'center',
                  border: '1px solid black',
                  transform: `translateX(${xOffset}%) scale(${scale})`,
                  zIndex,
                },
              },
              order
            );
          }
        )
      )
    );
  }

  function renderApp() {
    const id = '__root_two__';
    const domRoot = document.getElementById(id);
    const reactRoot = createRoot(domRoot);

    reactRoot.render(e(App));
  }

  renderApp();
})();
