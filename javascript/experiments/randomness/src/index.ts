import { createElement as e } from 'react';
import { createRoot } from 'react-dom/client';
// Workaround import because the library doesn't provide imports for CJS or MJS.
import { get_elements } from '@flexos/elements/dist/flexos-elements.umd';

const createSequenceWithMainElement = get_elements({
  length: 10,
});

function App() {
  return e(
    'main',
    null,
    e('h1', null, 'Use my library and play with Webpack and TypeScript'),
    e('p', null, 'Out of boredom play with my library and do:'),
    e(
      'ul',
      null,
      e('li', null, 'Create webpack configuration'),
      e('li', null, 'Create type declaration'),
      e('li', null, 'Create sequences to use the library')
    ),
    e('h2', null, 'Unmodified sequence'),
    e(
      'ul',
      null,
      createSequenceWithMainElement(3).map(({ order }) =>
        e('li', { key: order }, order)
      )
    ),
    e('h2', null, 'Each order combined with a string'),
    e(
      'ul',
      null,
      createSequenceWithMainElement(6).map(({ order }) =>
        e('li', { key: order }, `Order: ${order}`)
      )
    )
  );
}

function renderApp(): void {
  const id = 'app';
  const domRoot = document.getElementById(id);

  if (domRoot) {
    createRoot(domRoot).render(e(App));
  }
}

renderApp();
