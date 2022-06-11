import { useState } from 'react';
import { createRoot } from 'react-dom/client';
import styled from 'styled-components';
import './index.css';
// create images directory and place images in it
// create ./images/index.js and export default images as an array
import images from './images';

/**
 * A picture album.
 *
 * - Pictures are on top of each other.
 * - Below the pictures are buttons that we can use to set active picture.
 * - Newly visible picture has fade-in effect.
 * - The saved index is index of the currently visible picture.
 *   The images are array of file names.
 * - The first image is the default active image.
 * - The active image is on top of the others.
 *
 * - Get the design.
 */

const Article = styled.article`
  margin: 16px auto 0;
  width: 100%;
  max-width: 768px;
`;

const AlbumItems = styled.ul`
  background-color: #005f73;
  position: relative;
  display: flex;
  ::after {
    content: '';
    display: block;
    padding-top: 100%;
  }
`;

const AlbumItem = styled.li`
  height: 100%;
  width: 100%;
  position: absolute;
  opacity: ${({ isVisible }) => (isVisible ? 1 : 0)};
  list-style: none;
  transition: opacity 0.5s ease-in;
  z-index: ${({ isVisible }) => (isVisible ? 1 : 0)};
`;

const AlbumImage = styled.img`
  display: block;
  position: absolute;
  width: 100%;
  height: 100%;
  object-fit: scale-down;
`;

const Controls = styled.ul`
  margin-top: 16px;
  display: flex;
  justify-content: center;
`;

const Control = styled.li`
  list-style: none;
  :not(:last-child) {
    margin-right: 16px;
  }
`;

const ControlBtn = styled.button`
  display: block;
  border-style: none;
  border-radius: 50%;
  width: 35px;
  height: 35px;
  cursor: pointer;
  background-color: ${({ isVisible }) => (isVisible ? '#3e3e3e' : '')};
  :focus {
    outline: 2px solid #1645ff;
    box-shadow: 0 0 10px #1645ff;
  }
`;

// prevents focus styling on mouse action, preserves keyboard focus styling
// https://css-tricks.com/keyboard-only-focus-styles/#comment-1653279
const PreventMouseFocus = styled.span`
  display: block;
  width: 100%;
  height: 100%;
`;

const ControlLabel = styled.span`
  display: block;
  width: 1px;
  height: 1px;
  overflow: hidden;
`;

/**
 * Renders list of images and controls that set an active image.
 * Default active image is first in an array.
 * Returns a heading with a message if images are empty.
 */
function App() {
  // images may be an empty array
  const defaultIndex = images[0] ? 0 : undefined;
  const [visibleIndex, setVisibleIndex] = useState(defaultIndex);

  function show(index) {
    return () => {
      setVisibleIndex(index);
    };
  }

  // if images are empty, show useful message
  if (images.length === 0) {
    return (
      <Article>
        <h1>No images to show!</h1>
      </Article>
    );
  }

  let albumItems = [];
  let controls = [];

  // render album and controls in one go
  images.forEach((image, index) => {
    albumItems.push(
      <AlbumItem key={index} isVisible={index === visibleIndex}>
        <AlbumImage src={image} />
      </AlbumItem>
    );

    const label = `open image ${index + 1}`;

    controls.push(
      <Control key={index}>
        <ControlBtn
          title={label}
          aria-label={label}
          isVisible={index === visibleIndex}
          onClick={show(index)}
        >
          <PreventMouseFocus tabIndex="-1">
            <ControlLabel>{label}</ControlLabel>
          </PreventMouseFocus>
        </ControlBtn>
      </Control>
    );
  });

  return (
    <Article>
      <AlbumItems>{albumItems}</AlbumItems>
      <Controls>{controls}</Controls>
    </Article>
  );
}

createRoot(document.getElementById('app')).render(<App />);
