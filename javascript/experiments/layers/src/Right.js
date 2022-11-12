import { useState } from 'react';

function Right() {
  const [count, setCount] = useState(30);

  const increase = () => setCount((previousCount) => previousCount + 1);

  return (
    <section>
      <h1>Right count</h1>
      <p>Current count is {count}.</p>
      <button onClick={increase}>Increase</button>
    </section>
  );
}

export { Right };
