import { createElement as e, useEffect } from 'react';
import styled from 'styled-components';

const Title = styled.h1`
  color: red;
`;

function App() {
  useEffect(() => {
    console.log('Hello World lol wtf');
  }, []);

  return e(Title, null, 'Hello World');
}

export { App };
