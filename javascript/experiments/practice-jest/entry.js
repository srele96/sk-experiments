import { createElement as e } from 'react';
import { App } from './App';
import { createRoot } from 'react-dom/client';
import { Provider } from 'react-redux';
// https://stackoverflow.com/questions/71944111/redux-createstore-is-deprecated-cannot-get-state-from-getstate-in-redux-ac
// https://redux.js.org/introduction/why-rtk-is-redux-today
import { combineReducers, createStore } from 'redux';

createRoot(document.getElementById('root')).render(
  e(
    Provider,
    {
      store: createStore(
        combineReducers({
          foo(state = new Set(), action) {
            switch (action.type) {
              case 'foo/add':
                return new Set(state).add(action.payload);
              default:
                return state;
            }
          },
          bar(state = new Set(), action) {
            switch (action.type) {
              case 'bar/add':
                return new Set(state).add(action.payload);
              default:
                return state;
            }
          },
        })
      ),
    },
    e(App)
  )
);
