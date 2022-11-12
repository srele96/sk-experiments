import styles from './Layer.module.scss';

function Layer(props) {
  const fullHeightPreventsClickOnLayerBehind = 0;

  return (
    <li
      style={{
        transform: props.layer.moveToTopLayer,
        zIndex: props.layer.zIndex,
        width: props.size.layerWidth,
        height: fullHeightPreventsClickOnLayerBehind,
      }}
      className={[styles.onTopOfEachOther, styles.allowClickOnLayerBehind].join(
        ' '
      )}
    >
      <div
        style={{
          transform: props.layer.moveFromTopLayer,
          width: props.size.layerWidth,
        }}
        className={styles.allowClickOnLayerBehind}
      >
        <button
          style={{
            transform: props.layer.scale,
            width: props.size.layerWidth,
            height: props.size.containerHeight,
          }}
          className={styles.navigation}
        >
          <img
            className={styles.picture}
            src={props.layer.data.src}
            alt={props.layer.data.alt}
          />
        </button>
      </div>
    </li>
  );
}

export { Layer };
