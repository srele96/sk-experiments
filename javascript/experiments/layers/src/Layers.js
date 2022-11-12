import { useState } from 'react';

import { getSize } from './getSize';
import { moveAroundTopLayer } from './moveAroundTopLayer';

import styles from './Layers.module.scss';

function Layers() {
  const [size] = useState(getSize());
  const [layers] = useState(moveAroundTopLayer);

  return (
    <ul style={{ width: size.containerWidth, height: size.containerHeight }}>
      {layers.map((layer, i) => {
        return (
          <li
            style={{
              width: size.layerWidth,
              height: size.containerHeight,
              transform: layer.moveToTopLayer,
              zIndex: layer.zIndex,
            }}
            className={styles.onTopOfEachOther}
            key={i}
          >
            <button style={{ transform: layer.moveFromTopLayer }}>
              <img
                style={{ transform: layer.scale }}
                src={layer.data.src}
                alt={layer.data.alt}
              />
            </button>
          </li>
        );
      })}
    </ul>
  );
}

export { Layers };
