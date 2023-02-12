(() => {
  // TODO(add types): I would like to have better type system for JS.

  function createSierpinskiPointsGenerator(options) {
    const generateSierpinskiPoints = (() => {
      // Encapsulate private variables to abide Single Responsibility Principle.
      const changeAngle = 120;
      const scaleLength = 0.5;
      const changeLevel = 1;

      return function generateSierpinskiPoints({ from, angle, length, level }) {
        if (level > 0) {
          const left = point({ from, angle: angle - changeAngle, length });
          const top = point({ from, angle, length });
          const right = point({ from, angle: angle + changeAngle, length });

          options.onPointsGeneration({ from, left, top, right });

          generateSierpinskiPoints({
            from: left,
            angle: angle - changeAngle,
            length: length * scaleLength,
            level: level - changeLevel,
          });
          generateSierpinskiPoints({
            from: top,
            angle,
            length: length * scaleLength,
            level: level - changeLevel,
          });
          generateSierpinskiPoints({
            from: right,
            angle: angle + changeAngle,
            length: length * scaleLength,
            level: level - changeLevel,
          });
        }
      };
    })();

    return function sierpinskiPointsGenerator(sierpinskiOptions) {
      options.onBeforeGeneration(sierpinskiOptions.from);
      generateSierpinskiPoints(sierpinskiOptions);
      options.onAfterGeneration();
    };
  }

  function drawSierpinski() {
    const id = 'sierpinski';
    const canvas = document.getElementById(id);
    const ctx = canvas.getContext('2d');

    const generateSierpinskiPoints = createSierpinskiPointsGenerator({
      onBeforeGeneration(point) {
        ctx.beginPath();
        ctx.moveTo(point.x, point.y);
      },
      onPointsGeneration({ from, left, top, right }) {
        const moveToBase = () => ctx.moveTo(from.x, from.y);

        moveToBase();
        ctx.lineTo(left.x, left.y);

        moveToBase();
        ctx.lineTo(top.x, top.y);

        moveToBase();
        ctx.lineTo(right.x, right.y);
      },
      onAfterGeneration() {
        ctx.stroke();
        ctx.closePath();
      },
    });

    generateSierpinskiPoints({
      from: { x: 180, y: 200 },
      angle: -90,
      length: 50,
      level: 10,
    });
  }

  drawSierpinski();
})();
