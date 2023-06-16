import { useState } from 'react';
import { Pictures } from './Pictures';
import { Picture } from './Picture';
import { Navigations } from './Navigations';
import { Navigation } from './Navigation';

function Album(props) {
  const [visiblePicture, setVisiblePicture] = useState(0);

  function showPicture(index) {
    return () => {
      setVisiblePicture(index);
    };
  }

  function transformPicturesToJSX() {
    const pictures = [];
    const navigations = [];

    let descriptiveLabel = '';
    let isVisible = false;

    props.pictures.forEach((image, index) => {
      descriptiveLabel = `image ${index + 1}`;
      isVisible = index === visiblePicture;

      pictures.push(
        <Picture
          key={index}
          isVisible={isVisible}
          descriptiveLabel={descriptiveLabel}
          src={image}
        />
      );

      navigations.push(
        <Navigation
          key={index}
          isVisible={isVisible}
          descriptiveLabel={descriptiveLabel}
          showPicture={showPicture(index)}
        />
      );
    });

    return { pictures, navigations };
  }

  const { pictures, navigations } = transformPicturesToJSX();

  return (
    <div>
      <Pictures>{pictures}</Pictures>
      <Navigations>{navigations}</Navigations>
    </div>
  );
}

export { Album };
