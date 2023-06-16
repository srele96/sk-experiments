# ReactJS mouse-move throttle

Throttling mouse-move events in ReactJS. Throttle the event handler and save the coordinates to state. The hook must run only after the component is initially mounted.

## Throttling

Throttling examples:

- I decide to move a hundred steps but skip every second step (Throttle every second step).
- I decide to wave while I move for twenty seconds, but I wave every third second (Three-second throttle).

I hope you get the point.

## Mouse-move events

```jsx
console.clear();
console.log({ React, ReactDOM });
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

function PrintMouseMoveEvent() {
  React.useEffect(() => {
    document.addEventListener('mousemove', (event) => {
      console.log('mousemove', event);
    });
  });

  return <h1>Open console to see mouse-move event output</h1>;
}

ReactDOM.createRoot(document.getElementById('root')).render(
  <PrintMouseMoveEvent />
);
```

Mouse-move events get fired frequently. Too many events cause performance issues. Open the console with the Codepen example below to try it out.

In the picture below, you can see the mouse-move events.

## ReactJS philosophy

Use state to control the components. Following the ReactJS philosophy, I need to do the following:

Listen to mouse-move events.
Save the mouse-move events to the state.
Use the saved coordinates to move the header.

The mouse-move event provides mouse coordinates, and that is the hardest part.

## Component life cycle

THE FOLLOWING APPLIES TO FUNCTIONAL COMPONENTS!

I believe the components have two different types of life cycles.

The component becomes available in the DOM.
The component state is updated.

### The components birth

The component uses the initial state only once when it is mounted.

I like to call it the components birth.

Setting the state in the component **does not destroy it**.

Conditional rendering is an example of the component's birth.

### Importance of understanding life cycle

The hooks are often the source of useless component updates.

The most important thing is to have a hook run when I want.

Attaching the mouse-move event listener only needs to happen after initial birth.

Removing the mouse-move event listener needs to happen before the component's removal.

## ReactJS mouse-move non-throttled

Easier to understand. The throttling adds layers of complexity.

First, the source code:

```jsx
console.clear();
console.log({ React, ReactDOM });
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

function createMousePosition(x, y) {
  return { x, y };
}

function MouseMove() {
  const [mousePosition, setMousePosition] = React.useState(
    createMousePosition(0, 0)
  );

  // i absolutely don't want to rerun this hook at any other time
  // then initial mount and last unmount
  React.useEffect(() => {
    // saveMousePosition must be defined in the hook
    // when a hook calls a function that references state or props
    // they must be declared in dependency array
    // if saveMousePosition is outside of the hook
    // i would need to use React.useCallback to wrap it
    function saveMousePosition(event) {
      setMousePosition(createMousePosition(event.clientX, event.clientY));
    }

    document.addEventListener('mousemove', saveMousePosition);
    return () => {
      document.removeEventListener('mousemove', saveMousePosition);
    };
  }, [setMousePosition]);

  return (
    <h1
      style={{
        position: 'absolute',
        top: `${mousePosition.y}px`,
        left: `${mousePosition.x}px`,
        transform: 'translate(-50%, -50%)',
        margin: 0,
      }}
    >
      reactjs mousemove non-throttled version
    </h1>
  );
}

const root = document.getElementById('root');
ReactDOM.createRoot(root).render(<MouseMove />);
```

- The component stores initial coordinates.
- Attach listener after component's birth.
- Remove listener before component's death.
- Update the component's state.

The Codepen runnable example:

[https://codepen.io/Flexos96/pen/eYVoYgJ?editors=0010](https://codepen.io/Flexos96/pen/eYVoYgJ?editors=0010)

## ReactJS mouse-move throttled

First, the source code for throttled version:

```jsx
console.clear();
console.log({ React, ReactDOM });
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

const DURATION = 10;

const throttle = (function () {
  let timeout = undefined;
  return function throttle(callback) {
    if (timeout === undefined) {
      callback();
      timeout = setTimeout(() => {
        // allow another call to be throttled
        timeout = undefined;
      }, DURATION);
    }
  };
})();

/**
 * Wraps callback in a function and throttles it.
 * @returns Wrapper function
 */
function throttlify(callback) {
  return function throttlified(event) {
    throttle(() => {
      callback(event);
    });
  };
}

function createMousePosition(x, y) {
  return { x, y };
}

function MouseMove() {
  const [mousePosition, setMousePosition] = React.useState(
    createMousePosition(0, 0)
  );

  // i absolutely don't want to rerun this hook at any other time
  // then initial mount and last unmount
  React.useEffect(() => {
    const saveMousePosition = throttlify((event) => {
      setMousePosition(createMousePosition(event.clientX, event.clientY));
    });

    document.addEventListener('mousemove', saveMousePosition);
    return () => {
      document.removeEventListener('mousemove', saveMousePosition);
    };
  }, [setMousePosition]);

  return (
    <h1
      style={{
        position: 'absolute',
        top: `${mousePosition.y}px`,
        left: `${mousePosition.x}px`,
        transform: 'translate(-50%, -50%)',
        margin: 0,
        transition: `${DURATION}ms linear`,
      }}
    >
      reactjs mousemove throttled version
    </h1>
  );
}

const root = document.getElementById('root');
ReactDOM.createRoot(root).render(<MouseMove />);
```

The only difference is throttling. I have two functions that handle throttling.

- The throttle function limits execution.
- The throttlify wraps around the argument and returns throttled version.

The throttle function doesn't allow me to do the cleanup. I don't have a reference for the event handler. Throttlify returns a throttled version so I can clean it up.

The Codepen runnable example:

[https://codepen.io/Flexos96/pen/qBxvQPV?editors=0010](https://codepen.io/Flexos96/pen/qBxvQPV?editors=0010)
