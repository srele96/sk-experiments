import { Fragment, createElement, useState, useEffect } from 'react';
import { createRoot } from 'react-dom/client';

const e = createElement;

function ProgressBar({ percentage }) {
  const percent = `${percentage}%`;

  return e(
    Fragment,
    {},
    e(
      'label',
      {
        style: {
          display: 'flex',
          flexDirection: 'column',
          width: 'fit-content',
          textAlign: 'center',
        },
      },
      percent,
      e(
        'progress',
        { id: 'progress-bar', value: percentage, max: 100 },
        percent
      )
    )
  );
}

function TimeoutAnimation() {
  const [percentage, setPercentage] = useState(0);

  useEffect(() => {
    if (percentage < 100) {
      setTimeout(() => setPercentage((prev) => prev + 1));
    }
  }, [percentage, setPercentage]);

  return e(ProgressBar, { percentage });
}

function RAFAnimation() {
  const [percentage, setPercentage] = useState(0);

  useEffect(() => {
    if (percentage < 100) {
      requestAnimationFrame(() => setPercentage((prev) => prev + 1));
    }
  }, [percentage, setPercentage]);

  return e(ProgressBar, { percentage });
}

function App() {
  return e(
    'section',
    {},
    e('h1', {}, 'JavaScript animations'),
    e('p', {}, 'This section shows animation with two different methods.'),
    e('h2', {}, 'Animation with timeout.'),
    e(
      'p',
      {},
      'Timeout produces lower-quality animations that may flicker and feel ' +
        'clunky or unnatural.'
    ),
    e(TimeoutAnimation),
    e('h2', {}, 'Animation with request animation frame.'),
    e(
      'p',
      {},
      'Request animation frame adjusts the calculation before each repaint' +
        ' which produces smoother results.'
    ),
    e(RAFAnimation)
  );
}

/**
 * Compares animation made with timeout and request animation frame.
 */
export function runProgressBarExample() {
  // html template doesn't exist, webpack doesn't support css
  const style = document.createElement('style');
  style.innerText = `
    * {
      box-sizing: border-box;
    }
  `;
  document.head.appendChild(style);

  const root = document.createElement('div');
  root.id = 'root';
  document.body.appendChild(root);

  createRoot(root).render(e(App));
}
