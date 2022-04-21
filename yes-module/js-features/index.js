const { createElement } = require('react');
const { createRoot } = require('react-dom');

const body = document.getElementsByTagName('body')[0];

(function shortCircuitingInRegularJavascript() {
  function getUser() {
    return {
      id: 1,
      displayName: 'Shrek',
      accountViews: 6,
    };
  }

  function getUserSection() {
    const user = getUser();

    const displayName = document.createElement('h2');
    const accountViews = document.createElement('p');
    const section = document.createElement('section');

    displayName.innerText = user.displayName;
    accountViews.innerText = `Account views: ${user.accountViews}`;
    section.appendChild(displayName);
    section.appendChild(accountViews);

    return section;
  }

  function getPermissionStatus(hasPermission) {
    const p = document.createElement('h2');
    p.innerText = `User ${
      hasPermission ? 'has ' : "doesn't have "
    } required permission`;

    return p;
  }

  const h1 = document.createElement('h1');
  h1.innerText = 'User profile page';

  body.appendChild(h1);

  let hasPermission = true;
  hasPermission && body.appendChild(getUserSection());

  // this makes no sense, however body.appendChild is never evaluated
  hasPermission = false;
  hasPermission && body.appendChild(getPermissionStatus(hasPermission));
})();

/**
 * Animate downloading progress bar that displays:
 *  - Total file size.
 *  - Downloaded size.
 *  - Current download speed.
 *  - Imitate changing download speed, no internet is stable.
 */
(function downloadProgressBarExample() {
  const e = createElement;

  const startAnimation = (function () {
    let _delay;
    let _running = true;

    function animate(callback) {
      requestAnimationFrame(() => {
        callback();

        if (_running) setTimeout(() => animate(callback), _delay);
      });
    }

    function cleanup() {
      _running = false;
    }

    /**
     * Initially sets callback on requestAnimationFrame call stack.
     *
     * Afterwards sets timeout to call new requestAnimationFrame after delay.
     *
     * @param {() => void} callback - Function executed on requestAnimationFrame.
     * @param {number} delay - Time between setTimeout and requestAnimationFrame
     * in milliseconds.
     *
     * @return {() => void} - Cleanup function, terminates onward execution.
     */
    return function startAnimation(callback, delay = 500) {
      _delay = delay;
      animate(callback);

      return cleanup;
    };
  })();

  function AnimateDownloadingProgressBar() {
    return e(
      'div',
      { style: { width: 'min-content' } },
      e(
        'div',
        {
          style: {
            width: '300px',
            height: '50px',
            border: '5px solid black',
          },
        },
        e(
          'div',
          {
            style: {
              width: '18%',
              height: '100%',
              backgroundColor: 'black',
            },
          },
          null
        )
      ),
      e('p', { style: { textAlign: 'center' } }, 'Downloaded 18% of 187mb'),
      e('p', { style: { textAlign: 'center' } }, 'Download speed 378kb/s')
    );
  }

  const style = document.createElement('style');
  style.innerText = '*{ box-sizing: border-box; }';

  const head = document.getElementsByTagName('head')[0];
  head.appendChild(style);

  const root = document.createElement('div');
  root.id = 'root';

  body.appendChild(root);

  createRoot(root).render(e(AnimateDownloadingProgressBar));
})();
