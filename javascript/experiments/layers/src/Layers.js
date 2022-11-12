import { useState } from 'react';

import { getSize } from './getSize';
import { moveAroundTopLayer } from './moveAroundTopLayer';

import styles from './Layers.module.scss';

function Layers() {
  const [size] = useState(getSize());
  const [layers] = useState(moveAroundTopLayer);

  const fullHeightPreventsClickOnLayerBehind = 0;

  return (
    <ul style={{ width: size.containerWidth, height: size.containerHeight }}>
      {layers.map((layer, i) => {
        return (
          <li
            style={{
              width: size.layerWidth,
              height: fullHeightPreventsClickOnLayerBehind,
              transform: layer.moveToTopLayer,
              zIndex: layer.zIndex,
            }}
            className={styles.onTopOfEachOther}
            key={i}
          >
            <div style={{ transform: layer.moveFromTopLayer }}>
              <button
                style={{
                  width: size.layerWidth,
                  height: size.containerHeight,
                  transform: layer.scale,
                }}
              >
                <img
                  className={styles.picture}
                  src={layer.data.src}
                  alt={layer.data.alt}
                />
              </button>
            </div>
          </li>
        );
      })}
    </ul>
  );
}

export { Layers };
