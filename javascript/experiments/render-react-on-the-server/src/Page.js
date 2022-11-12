// Mock component for the SSR.
function Page(props) {
  return (
    <main>
      <h1>{props.title}</h1>
      <p>{props.content}</p>
    </main>
  );
}

export { Page };
