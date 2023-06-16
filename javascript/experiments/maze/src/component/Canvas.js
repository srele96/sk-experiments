import { createElement as e, useRef, useEffect } from 'react';

function Canvas(props) {
  const ref = useRef();

  useEffect(() => {
    const context = '2d';
    props.onContext2d(ref.current.getContext(context));
  }, [props.onContext2d]);

  return e('canvas', {
    ref,
    width: props.width,
    height: props.height,
  });
}

export { Canvas };
