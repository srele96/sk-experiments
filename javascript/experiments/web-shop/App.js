import { useState } from 'react';

const increment = 1;
const decrement = -1;

function App() {
  const [count, setCount] = useState(0);

  function changeBy(value) {
    return () => setCount((previousCount) => previousCount + value);
  }

  return (
    <div>
      <p>Wohooo! My interactive piece of web page!</p>
      <p>HMR works as well! Cool!</p>
      <button onClick={changeBy(increment)}>Increment</button>
      <button onClick={changeBy(decrement)}>Decrement</button>
      <p>The current count is: {count}</p>
    </div>
  );
}

export { App };
