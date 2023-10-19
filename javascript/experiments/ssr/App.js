import { createElement as e, useEffect } from 'react';

function App() {
  // The problem is fairly complex.
  // The data has to fetch on the server and the client.
  // The data has to be fetched on the server for the initial render.
  // The data does not need to be fetched on initial client side render.
  // The data should be fetched on subsequent client side renders.
  // (Later): The user should be able to refetch the data on demand.
  //
  // The engineers need to learn more about the problem domain.
  // They need to define the problem clearly.
  // Then they need to start thinking about the constraints, the trade-offs.
  // Then they need to think about possible solutions, public APIs, etc.
  //
  // Then there is probably an experimental phase where they try out the
  // solution and gather feedback from their users.
  //
  // Efficient algorithms and data structures are only a part of the software
  // engineering process. I start to understand why the ReactJS team uses RFCs.
  //
  // Some problems:
  // - fetching data on the client and the server
  // - how do we expose the user the data to fetch
  // - and more...
  // const { state, loading, error } = useData({
  //   before: () => {
  //     //
  //   },
  //   after: () => {
  //     //
  //   },
  //   select: (state) => {
  //     // select the data i want to use in my component
  //   },
  // });

  useEffect(() => {
    console.log('Hello World!');
  }, []);

  return e('h1', null, 'Hello World');
}

export { App };
