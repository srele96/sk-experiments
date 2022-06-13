import styled from 'styled-components';

const StyledPictures = styled.ul`
  background-color: var(--blue-level-1);
  position: relative;
  display: flex;

  ::after {
    content: '';
    display: block;
    padding-top: 65%;
  }
`;

function Pictures({ children }) {
  return <StyledPictures>{children}</StyledPictures>;
}

export { Pictures };
