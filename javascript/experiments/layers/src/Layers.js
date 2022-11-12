import { useState } from 'react';

import { getSize } from './getSize';
import { moveAroundTopLayer } from './moveAroundTopLayer';

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
              transform: layer.moveToTopLayer,
              zIndex: layer.zIndex,
            }}
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
