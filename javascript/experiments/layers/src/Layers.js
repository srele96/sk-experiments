import { useState } from 'react';

import { getSize } from './getSize';
import { moveAroundTopLayer } from './moveAroundTopLayer';

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
        return (
          <li
            style={{
              transform: layer.moveToTopLayer,
              zIndex: layer.zIndex,
              width: size.layerWidth,
              height: fullHeightPreventsClickOnLayerBehind,
            }}
            className={styles.onTopOfEachOther}
            key={i}
          >
            <div
              style={{
                transform: layer.moveFromTopLayer,
                width: size.layerWidth,
                height: fullHeightPreventsClickOnLayerBehind,
              }}
            >
              <button
                style={{
                  transform: layer.scale,
                  width: size.layerWidth,
                  height: size.containerHeight,
                }}
                className={styles.navigation}
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
