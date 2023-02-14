(() => {
  const calculate = {
    radians(degree) {
      return degree * (Math.PI / 180);
    },
    point({ from, angle, length }) {
      return {
        x: from.x + length * Math.cos(calculate.radians(angle)),
        y: from.y + length * Math.sin(calculate.radians(angle)),
      };
    },
  };

  // Take options so we can separate the point generation from the logic using
  // generated points.
  function createSierpinskiPointsGenerator(options) {
    const generateSierpinskiPoints = (() => {
      // Use IIFE - Immediately Invoked Function Expression to encapsulate
      // private variables to abide Single Responsibility Principle. I don't
      // want to create these values inside the algorithm.
      function rotateLeft(angle) {
        return angle - options.changeAngle;
      }
      function rotateRight(angle) {
        return angle + options.changeAngle;
      }
      function scale(length) {
        return length * options.scaleLength;
      }
      const changeLevelBy = 1;
      function changeLevel(level) {
        return level - changeLevelBy;
      }

      return function generateSierpinskiPoints({ from, angle, length, level }) {
        if (level > 0) {
          const left = calculate.point({
            from,
            angle: rotateLeft(angle),
            length,
          });
          const top = calculate.point({
            from,
            angle,
            length,
          });
          const right = calculate.point({
            from,
            angle: rotateRight(angle),
            length,
          });

          options.onPointsGeneration({ from, left, top, right });

          generateSierpinskiPoints({
            from: left,
            angle: rotateLeft(angle),
            length: scale(length),
            level: changeLevel(level),
          });
          generateSierpinskiPoints({
            from: top,
            angle,
            length: scale(length),
            level: changeLevel(level),
          });
          generateSierpinskiPoints({
            from: right,
            angle: rotateRight(angle),
            length: scale(length),
            level: changeLevel(level),
          });
        }
      };
    })();

    return function sierpinskiPointsGenerator(sierpinskiOptions) {
      options.onBeforeGeneration();
      generateSierpinskiPoints(sierpinskiOptions);
      options.onAfterGeneration();
    };
  }

  const e = React.createElement;

  function Canvas(props) {
    // Wrap imperative useRef API to be used declaratively.
    const ref = React.useRef();

    React.useEffect(() => {
      const context = '2d';
      // Context is ready, provide it to the client.
      props.onContext2d(ref.current.getContext(context));
    }, [props.onContext2d]);

    return e('canvas', { ref, width: props.width, height: props.height });
  }

  function App() {
    const changeAngleId = 'change-angle';
    const minimumChangeAngle = 0;
    const maximumChangeAngle = 120;
    const changeByOne = 1;
    const defaultChangeAngle = maximumChangeAngle;
    const [changeAngle, setChangeAngle] = React.useState(defaultChangeAngle);
    function saveChangeAngle(event) {
      // We receive value as a string and it has to be parsed.
      setChangeAngle(Number(event.target.value));
    }

    const scaleLengthId = 'scale-length';
    const minimumScaleLength = 0.1;
    const maximumScaleLength = 0.5;
    const changeByPointOne = 0.1;
    const defaultScaleLength = maximumScaleLength;
    const [scaleLength, setScaleLength] = React.useState(defaultScaleLength);
    function saveScaleLength(event) {
      // We receive value as a string and it has to be parsed.
      setScaleLength(Number(event.target.value));
    }

    // Fit the small phone screens in case someone opens CodePen on the device
    // with a really small screen.
    const width = 300;
    const height = 300;

    function createOptions() {
      const half = 2;
      const halfWidth = width / half;
      const halfHeight = height / half;
      const center = { x: halfWidth, y: halfHeight };

      const toUpside = -90;
      const fitsOnScreen = 50;
      // NOTE!
      // I tried using value 10 but it causes performance issues such as
      // noticeable slowdown of the browser. Repeated redraws cause the
      // memory usage of browser to skyrocket. I found value 8 to be
      // performant and dense enough at the same time.
      const highDensity = 8;

      const options = {
        from: center,
        angle: toUpside,
        length: fitsOnScreen,
        level: highDensity,
      };

      return options;
    }

    function drawSierpinskiGasket(ctx) {
      function clearScreenAndPrepareItForDrawing() {
        const fromX = 0;
        const fromY = 0;

        ctx.clearRect(fromX, fromY, width, height);
        ctx.beginPath();
      }

      function moveTo(point) {
        ctx.moveTo(point.x, point.y);
      }

      function lineTo(point) {
        ctx.lineTo(point.x, point.y);
      }

      function connectPoints({ from, left, top, right }) {
        moveTo(from);
        lineTo(left);

        moveTo(from);
        lineTo(top);

        moveTo(from);
        lineTo(right);
      }

      function finishDrawing() {
        ctx.stroke();
        ctx.closePath();
      }

      const generateSierpinskiGasketPoints = createSierpinskiPointsGenerator({
        changeAngle,
        scaleLength,
        onBeforeGeneration: clearScreenAndPrepareItForDrawing,
        onPointsGeneration: connectPoints,
        onAfterGeneration: finishDrawing,
      });

      generateSierpinskiGasketPoints(createOptions());
    }

    return e(
      React.Fragment,
      null,
      e(Canvas, { width, height, onContext2d: drawSierpinskiGasket }),
      e('p', null, 'Change values'),
      e(
        'label',
        { htmlFor: changeAngleId },
        e('div', null, `Angle: ${changeAngle}`),
        e('input', {
          type: 'range',
          id: changeAngleId,
          min: minimumChangeAngle,
          max: maximumChangeAngle,
          step: changeByOne,
          value: changeAngle,
          onChange: saveChangeAngle,
        })
      ),
      e(
        'label',
        { htmlFor: scaleLengthId },
        e('div', null, `Scale Length: ${scaleLength}`),
        e('input', {
          type: 'range',
          id: scaleLengthId,
          min: minimumScaleLength,
          max: maximumScaleLength,
          step: changeByPointOne,
          value: scaleLength,
          onChange: saveScaleLength,
        })
      )
    );
  }

  const id = 'modifiable-sierpinski';
  const domRoot = document.getElementById(id);
  const reactRoot = ReactDOM.createRoot(domRoot);
  reactRoot.render(e(App));
})();
