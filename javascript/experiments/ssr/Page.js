import { createElement as e } from 'react';

function Page(props) {
  return e(
    'html',
    null,
    e(
      'head',
      null,
      e('meta', { charSet: 'utf-8' }),
      e('meta', {
        name: 'viewport',
        content: 'width=device-width, initial-scale=1',
      }),
      e('title', null, props.title)
    ),
    e(
      'body',
      null,
      e('div', { id: 'root' }, props.children),
      e('script', { src: '/client.js' }),
      e(
        'script',
        {
          dangerouslySetInnerHTML: {
            __html: `window.__INITIAL_STATE__ = ${JSON.stringify(
              props.initialState
              // Sanitize initial state to prevent XSS attacks.
            ).replace(/</g, '\\u003c')}`,
          },
        },
        null
      )
    )
  );
}

export { Page };
