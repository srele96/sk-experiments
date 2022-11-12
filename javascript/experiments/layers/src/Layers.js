import { useState } from 'react';

import { getSize } from './getSize';
import { moveAroundTopLayer } from './moveAroundTopLayer';

import { Layer } from './Layer';

import styles from './Layers.module.scss';

function Layers() {
  const [size] = useState(getSize());
  const [layers] = useState(moveAroundTopLayer);

  const fullHeightPreventsClickOnLayerBehind = 0;

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
