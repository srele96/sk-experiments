(() => {
  const Canvas = {
    props: {
      width: {
        type: Number,
        required: true,
      },
      height: {
        type: Number,
        required: true,
      },
      onContext2d: {
        type: Function,
        required: true,
      },
    },
    mounted() {
      const context = '2d';
      this.onContext2d(this.$refs.canvas.getContext(context));
    },
    template: `
      <canvas
        ref="canvas"
        :width="width"
        :height="height"
      ></canvas>
    `,
  };

  function createSierpinskiCarpetValuesGenerator(options) {
    const generateSierpinskiCarpetValues = (function () {
      function hasMoreLevels(level) {
        return level > 0;
      }

      function oneThird(value) {
        return value / 3;
      }

      function oneLess(value) {
        return value - 1;
      }

      function calculateOffset({ from, distance }) {
        return from + distance;
      }

      function generateSierpinskiCarpetValues({
        xLeftOffset,
        yTopOffset,
        width,
        height,
        level,
      }) {
        if (hasMoreLevels(level)) {
          const oneThirdWidth = oneThird(width);
          const oneThirdHeight = oneThird(height);
          const xCenterOffset = calculateOffset({
            from: xLeftOffset,
            distance: oneThirdWidth,
          });
          const yCenterOffset = calculateOffset({
            from: yTopOffset,
            distance: oneThirdHeight,
          });

          // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

          options.onValueGeneration({
            xLeftOffset: xCenterOffset,
            yTopOffset: yCenterOffset,
            width: oneThirdWidth,
            height: oneThirdHeight,
          });

          // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

          const currentLevel = oneLess(level);

          const topLeft = {
            xLeftOffset,
            yTopOffset,
            width: oneThirdWidth,
            height: oneThirdHeight,
            level: currentLevel,
          };
          generateSierpinskiCarpetValues(topLeft);

          const topCenter = {
            xLeftOffset: xCenterOffset,
            yTopOffset,
            width: oneThirdWidth,
            height: oneThirdHeight,
            level: currentLevel,
          };
          generateSierpinskiCarpetValues(topCenter);

          const xRightOffset = calculateOffset({
            from: xCenterOffset,
            distance: oneThirdWidth,
          });

          const topRight = {
            xLeftOffset: xRightOffset,
            yTopOffset,
            width: oneThirdWidth,
            height: oneThirdHeight,
            level: currentLevel,
          };
          generateSierpinskiCarpetValues(topRight);

          const centerLeft = {
            xLeftOffset,
            yTopOffset: yCenterOffset,
            width: oneThirdWidth,
            height: oneThirdHeight,
            level: currentLevel,
          };
          generateSierpinskiCarpetValues(centerLeft);

          const centerRight = {
            xLeftOffset: xRightOffset,
            yTopOffset: yCenterOffset,
            width: oneThirdWidth,
            height: oneThirdHeight,
            level: currentLevel,
          };
          generateSierpinskiCarpetValues(centerRight);

          const yDownOffset = calculateOffset({
            from: yCenterOffset,
            distance: oneThirdHeight,
          });

          const downLeft = {
            xLeftOffset,
            yTopOffset: yDownOffset,
            width: oneThirdWidth,
            height: oneThirdHeight,
            level: currentLevel,
          };
          generateSierpinskiCarpetValues(downLeft);

          const downCenter = {
            xLeftOffset: xCenterOffset,
            yTopOffset: yDownOffset,
            width: oneThirdWidth,
            height: oneThirdHeight,
            level: currentLevel,
          };
          generateSierpinskiCarpetValues(downCenter);

          const downRight = {
            xLeftOffset: xRightOffset,
            yTopOffset: yDownOffset,
            width: oneThirdWidth,
            height: oneThirdHeight,
            level: currentLevel,
          };
          generateSierpinskiCarpetValues(downRight);
        }
      }

      return generateSierpinskiCarpetValues;
    })();

    function sierpinskiCarpetValuesGenerator(initialValues) {
      options.onBeforeGeneration();
      generateSierpinskiCarpetValues(initialValues);
      options.onAfterGeneration();
    }

    return sierpinskiCarpetValuesGenerator;
  }

  const app = Vue.createApp({
    components: {
      Canvas,
    },
    methods: {
      drawSierpinskiCarpet(ctx) {
        const beginX = 0;
        const beginY = 0;
        const width = this.$data.width;
        const height = this.$data.height;

        function clearAndPrepareCanvas() {
          ctx.clearRect(beginX, beginY, width, height);
          ctx.beginPath();
          ctx.fillStyle = 'black';
        }

        function fillRectangle({ xLeftOffset, yTopOffset, width, height }) {
          ctx.fillRect(xLeftOffset, yTopOffset, width, height);
        }

        function draw() {
          ctx.closePath();
          ctx.stroke();
        }

        const generateSierpinskiCarpetValues =
          createSierpinskiCarpetValuesGenerator({
            onBeforeGeneration: clearAndPrepareCanvas,
            onValueGeneration: fillRectangle,
            onAfterGeneration: draw,
          });

        // Don't generate too many to preserve performance.
        const level = 5;

        const wholeCanvas = {
          xLeftOffset: beginX,
          yTopOffset: beginY,
          width,
          height,
          level,
        };
        generateSierpinskiCarpetValues(wholeCanvas);
      },
    },
    data() {
      const width = 300;
      const height = 300;

      return { width, height };
    },
    template: `
      <Canvas
        :width="width"
        :height="height"
        :onContext2d="drawSierpinskiCarpet"
      />
    `,
  });

  const id = 'sierpinski-carpet';
  const domRoot = document.getElementById(id);
  app.mount(domRoot);
})();
