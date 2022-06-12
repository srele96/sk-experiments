import styled from 'styled-components';

const StyledNavigation = styled.li`
  list-style: none;

  :not(:last-child) {
    margin-right: 8px;
  }
`;

const Navigate = styled.button`
  background-color: ${({ isVisible }) =>
    `var(--level-${isVisible ? '4' : '3'})`};
  display: block;
  width: 16px;
  height: 16px;
  border-style: none;
  border-radius: 50%;
  cursor: pointer;
  transition: background-color 0.5s ease-in;

  :focus {
    outline: 2px solid var(--level-4);
    box-shadow: 0 0 10px var(--level-4);
  }
`;

const CaptureMouseClickFocus = styled.span`
  display: block;
  width: 100%;
  height: 100%;
`;

const HideDescriptiveLabelKeepAccessibility = styled.span`
  display: block;
  width: 1px;
  height: 1px;
  overflow: hidden;
`;

function Navigation({ descriptiveLabel, showPicture, isVisible }) {
  return (
    <StyledNavigation>
      <Navigate
        isVisible={isVisible}
        onClick={showPicture}
        title={descriptiveLabel}
        aria-label={descriptiveLabel}
      >
        <CaptureMouseClickFocus tabIndex="-1">
          <HideDescriptiveLabelKeepAccessibility>
            {descriptiveLabel}
          </HideDescriptiveLabelKeepAccessibility>
        </CaptureMouseClickFocus>
      </Navigate>
    </StyledNavigation>
  );
}

export { Navigation };
