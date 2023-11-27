function foo(state = new Set(), action) {
  switch (action.type) {
    case 'foo/add':
      return new Set(state).add(action.payload);
    default:
      return state;
  }
}

function bar(state = new Set(), action) {
  switch (action.type) {
    case 'bar/add':
      return new Set(state).add(action.payload);
    default:
      return state;
  }
}

export { foo, bar };
