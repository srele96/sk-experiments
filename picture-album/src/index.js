import { createRoot } from 'react-dom/client';
// create images directory and place images in it
// create ./images/index.js and export default images as an array
import images from './images';

console.log(images);
/**
 * A picture album.
 *
 * - Pictures are on top of each other.
 * - Below the pictures are dots that we can use to set active picture.
 * - The picture that shows fades in.
 * - The saved picture file name is visible.
 *   The images are array of file names.
 * - The default visible image is first picture.
 * - The active image is on top of the others.
 */

function App() {
  return (
    <ul>
      {images.map((image) => (
        <li key={image}>
          <img src={image} alt={image} />
        </li>
      ))}
    </ul>
  );
}

createRoot(document.getElementById('app')).render(<App />);
