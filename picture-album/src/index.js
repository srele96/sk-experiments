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
 * - The picture container is a rectangle with darker background than page.
 */

/**
 * A page container.
 */
const Article = styled.article`
  margin: 0 auto;
  width: 100%;
  max-width: 1080px;
`;

/**
 * Container for all images.
 */
const AlbumItems = styled.ul`
  background-color: #001219;
  position: relative;
  display: flex;
  ::after {
    content: '';
    display: block;
    padding-top: 65%;
  }
`;

/**
 * Container for an image with controllable opacity and z-index.
 */
const AlbumItem = styled.li`
  height: 100%;
  width: 100%;
  position: absolute;
  list-style: none;
  transition: opacity 0.5s ease-in;
  opacity: ${({ isVisible }) => (isVisible ? 1 : 0)};
  z-index: ${({ isVisible }) => (isVisible ? 1 : 0)};
`;

/**
 * Responsive image. Scales to fit a container. The whole image is visible.
 */
const AlbumImage = styled.img`
  display: block;
  position: absolute;
  width: 100%;
  height: 100%;
  object-fit: scale-down;
`;

/**
 * Controls container.
 */
const Controls = styled.ul`
  margin-top: 6px;
  display: flex;
  justify-content: center;
`;

/**
 * An image control container.
 */
const Control = styled.li`
  list-style: none;
  :not(:last-child) {
    margin-right: 8px;
  }
`;

/**
 * A control button with controllable background-color.
 */
const ControlBtn = styled.button`
  display: block;
  border-style: none;
  border-radius: 50%;
  width: 16px;
  height: 16px;
  cursor: pointer;
  transition: background-color 0.5s ease-in;
  background-color: ${({ isVisible }) => (isVisible ? '#94d2bd' : '#0a9396')};
  :focus {
    outline: 2px solid #e9d8a6;
    box-shadow: 0 0 10px #e9d8a6;
  }
`;

/**
 * Prevents focus styling on mouse action, preserves keyboard focus styling.
 *
 * Pass a prop tabIndex="-1" to prevent mouse actions activating outline on the
 * parent.
 *
 * [keyboard-only-focus-styles](https://css-tricks.com/keyboard-only-focus-styles/#comment-1653279)
 */
const PreventMouseFocus = styled.span`
  display: block;
  width: 100%;
  height: 100%;
`;

/**
 * The text is hidden but accessible.
 */
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
        <AlbumImage src={image} alt={image} />
      </AlbumItem>
    );

    const label = `open image ${index + 1}`;

    // We hide the text of the control for nicer appearance
    // I used label and title to make the button accessible
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
