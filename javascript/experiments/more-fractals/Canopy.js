(() => {
  // TODO(reuse types): Find a way to reuse types across multiple files.

  /**
   * @typedef {Object} Point
   * @property {number} Point.x
   * @property {number} Point.y
   */

  /**
   * @typedef {(point: Point) => void} UsePoint
   */

  /**
   * @typedef {() => void} Handler
   */

  /**
   * @typedef {Object} CanopyOptions
   * @property {Point} CanopyOptions.from
   * @property {number} CanopyOptions.angle
   * @property {number} CanopyOptions.length
   * @property {number} CanopyOptions.level
   */

  /**
   * @param {Object} options
   * @param {UsePoint} options.useInitialPoint
   * @param {UsePoint} options.useSubsequentPoint
   * @param {Handler} options.onBeforeGenerate
   * @param {Handler} options.onAfterGenerate
   */
  function createCanopyPointsGenerator(options = {}) {
    const changeLeftAngle = 30;
    const scaleLeftLength = 0.8;

    const changeRightAngle = 30;
    const scaleRightLength = 0.8;

    const changeLevel = 1;

    /**
     * @param {CanopyOptions} canopyOptions
     */
    function generateCanopyPoints({ from, angle, length, level }) {
      if (level > 0) {
        generateCanopyPoints({
          from: point({
            from,
            angle,
            length,
          }),
          angle: angle - changeLeftAngle,
          length: length * scaleLeftLength,
          level: level - changeLevel,
        });
        generateCanopyPoints({
          from: point({
            from,
            angle,
            length,
          }),
          angle: angle + changeRightAngle,
          length: length * scaleRightLength,
          level: level - changeLevel,
        });
        options.useSubsequentPoint(from);
      } else {
        options.useInitialPoint(from);
      }
    }

    /**
     * @param {CanopyOptions} canopyOptions
     */
    return function canopyPointsGenerator(canopyOptions) {
      options.onBeforeGenerate();
      generateCanopyPoints(canopyOptions);
      options.onAfterGenerate();
    };
  }

  function drawCanopy() {
    const id = 'canopy';
    const canvas = document.getElementById(id);
    const ctx = canvas.getContext('2d');

    /**
     * @return {CanopyOptions}
     */
    function createSettings() {
      const bottomOffset = 50;
      const midBottom = {
        x: canvas.clientWidth / 2,
        y: canvas.clientHeight - bottomOffset,
      };
      const initialAngle = -90;
      const initialLength = 50;
      const level = 10;

      /** @type {CanopyOptions} */
      const settings = {
        from: midBottom,
        angle: initialAngle,
        length: initialLength,
        level,
      };

      return settings;
    }

    const generateCanopyPoints = createCanopyPointsGenerator({
      useInitialPoint(point) {
        ctx.moveTo(point.x, point.y);
      },
      useSubsequentPoint(point) {
        ctx.lineTo(point.x, point.y);
      },
      onBeforeGenerate() {
        ctx.beginPath();
      },
      onAfterGenerate() {
        ctx.stroke();
        ctx.closePath();
      },
    });

    generateCanopyPoints(createSettings());
  }

  drawCanopy();
})();
