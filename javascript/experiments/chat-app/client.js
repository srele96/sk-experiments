import { createRoot } from 'react-dom/client';
import styles from './client.module.css';
import { useEffect, createContext, useState, useContext } from 'react';
import axios from 'axios';
import { v4 } from 'uuid';

const DataContext = createContext({});

export { DataContext };

const promises = [];

function getInitialData() {
  return new Promise((resolve) => {});
}

/**
 *
 * @param {Object} options
 * @param {Promise<any>} options.promise
 */
function useAxiosPromise({ promise }) {
  const ctx = useContext(DataContext);

  const isServer = typeof window === 'undefined';

  if (isServer) {
    promise
      .then(console.log)
      .catch(console.error)
      .finally(() => {
        console.log('Finally');
      });
  }

  useEffect(() => {
    console.log(promise);
  }, [promise]);

  console.log(ctx);
}

function PageOne() {
  const [_remount, setRemount] = useState(0);

  if (_remount === 0) {
    setRemount((prev) => prev + 1);
  }

  const a = useAxiosPromise({
    promise: new Promise((resolve, reject) => {
      axios
        .get('https://jsonplaceholder.typicode.com/todos/1')
        .then((response) => {
          console.log('response here');
          resolve('resolved');
        })
        .catch(reject);
    }),
  });

  console.log(_remount)

  return <h1>Page One</h1>;
}

function PageTwo() {
  return <h1>Page Two</h1>;
}

console.log('styles', styles);

if (typeof window !== 'undefined') {
  const root = document.getElementById('__root');
  createRoot(root).render(<PageOne />);
}

export { PageOne, PageTwo };
