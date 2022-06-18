import styled from 'styled-components';

const StyledPicture = styled.li`
  opacity: ${({ isVisible }) => (isVisible ? 1 : 0)};
  z-index: ${({ isVisible }) => (isVisible ? 1 : 0)};
  position: absolute;
  width: 100%;
  height: 100%;
  list-style: none;
  transition: opacity 0.5s ease-in;
`;

const StyledImage = styled.img`
  position: absolute;
  width: 100%;
  height: 100%;
  display: block;
  object-fit: scale-down;
`;

function Picture({ src, descriptiveLabel, isVisible }) {
  return (
    <StyledPicture isVisible={isVisible}>
      <StyledImage src={src} alt={descriptiveLabel} />
    </StyledPicture>
  );
}

export { Picture };
