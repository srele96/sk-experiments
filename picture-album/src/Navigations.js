import styled from 'styled-components';

const StyledNavigations = styled.ul`
  display: flex;
  justify-content: center;
  margin-top: 6px;
`;

function Navigations({ children }) {
  return <StyledNavigations>{children}</StyledNavigations>;
}

export { Navigations };
