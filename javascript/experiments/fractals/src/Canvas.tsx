import { ReactNode, useEffect, useRef } from 'react';

interface CanvasProps {
  context: (context: CanvasRenderingContext2D | null) => void;
}

function Canvas(props: CanvasProps): ReactNode {
  const canvas = useRef<HTMLCanvasElement>(null);

  useEffect(() => {
    if (canvas.current) {
      props.context(canvas.current.getContext('2d'));
    } else {
      throw new Error('Canvas must always be defined!');
    }
  }, [props.context]);

  return <canvas ref={canvas} />;
}

export { Canvas };
