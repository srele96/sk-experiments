{
  type Dispatch<T> = (newState: T) => void;
  type State<T> = [T, Dispatch<T>];

  // Infer the type user provides
  function useStateFirst<T extends unknown>(defaultState: T): State<T> {
    return [defaultState, (newState: T) => {}]; // Mock
  }

  // What is the difference?
  function useStateSecond<T = unknown>(defaultState: T): State<T> {
    return [defaultState, (newState: T) => {}]; // Mock
  }

  {
    const [counter, setCounter] = useStateFirst(0);
    const [counter2, setCounter2] = useStateSecond(0);
  }

  {
    // const [counter, setCounter] = useStateFirst<number>(''); // Error
    // const [counter2, setCounter2] = useStateSecond<number>(''); // Error
  }

  {
    const [counter, setCounter] = useStateFirst<number>(0);
    const [counter2, setCounter2] = useStateSecond<number>(0);
  }

  {
    const [counter, setCounter] = useStateFirst(0);
    const [counter2, setCounter2] = useStateSecond(0);
  }

  // Anything is assignable to unknown, but unknown is assignable to itself or
  // any.
  const name: unknown = 'John';
  // const name2: string = name; // Error
  const name2 = name; // Infers type `unknown`
  const name3: string = name as string;
}
