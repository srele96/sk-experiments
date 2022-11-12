import { useState } from 'react';

function Left() {
  const [count, setCount] = useState(5);

  const increase = () => setCount((previousCount) => previousCount + 1);

  return (
    <section>
      <h1>Left count</h1>
      <p>Current count is {count}.</p>
      <button onClick={increase}>Increase</button>
    </section>
  );
}

export { Left };
