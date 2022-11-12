import { useState } from 'react';

import { moveAroundTopLayer } from './moveAroundTopLayer';

function Layers() {
  const [layers] = useState(moveAroundTopLayer);

  return (
    <ul>
      {layers.map((layer, i) => {
        return (
          <li
            style={{ transform: layer.moveToTopLayer, zIndex: layer.zIndex }}
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
