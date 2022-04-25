# js-features

- short-circuit
- requestAnimationFrame (JavaScript animations)

## short-circuit

JavaScript evaluates boolean & expression to expression.
I wrote two almost good examples.

## RAF - requestAnimationFrame

I tried to create a progress bar animation using RAF. Then I wanted to use ReactJS, but the two are not a good combination.

According to the MDN article, game loops can use RAF. The callback passed gets executed before the browser repaints. Browser repaints as fast as the screen gets refreshed - framerate. Monitors with a 60hz refresh rate execute the callback 60 times, 140hz executes it 140 times, etc.

Game loops update the screen. In a calculation for a new value of x coordinate, the last moment to be called is ideally right before repaint occurs.

Setting state in ReactJS is asynchronous, and doing so in the request animation frame callback doesn't make sense.

Synchronous calculations make sense and should be here because animation with javascript timeout flickers. RAF performs smooth and correct animations.
