import { useState, useEffect } from 'react';

import { getSize } from '../getSize';
import { moveAroundTopLayer } from '../moveAroundTopLayer';

import { Layer } from './Layer';

import styles from './Layers.module.scss';

function Layers() {
  const [size, setSize] = useState(getSize());
  const [layers] = useState(moveAroundTopLayer);

  // Update size.
  useEffect(() => {
    const updateLayerSize = () => setSize(getSize());

    addEventListener('resize', updateLayerSize);

    return () => removeEventListener('resize', updateLayerSize);
  }, [setSize]);

  return (
    <ul
      style={{
        width: size.containerWidth,
        height: size.containerHeight,
      }}
      className={styles.layers}
    >
      {layers.map((layer, i) => {
        return <Layer key={i} size={size} layer={layer} />;
      })}
    </ul>
  );
}

export { Layers };
