{
  interface Constraint {
    name: string;
  }

  type MyType<Argument extends Constraint = Constraint> = (
    arg: Argument
  ) => void;

  // const wontWork: MyType<{ lastName: string }> = (arg) => {
  //   const name = arg.name;
  // };

  const requiresAtLeast: MyType<{ name: string }> = (arg) => {
    const name: string = arg.name;
  };

  const canExtend: MyType<{ name: string; lastName: string }> = (arg) => {
    const { name, lastName } = arg;
  };
}

{
  type Dispatcher<T> = (arg: T) => void;

  interface DefaultConstraint {
    name: string;
  }

  /**
   * ConsttrainedDispatcher with user configurable constraint for more
   * versatility.
   */
  type ConstrainedDispatcher<
    UserConstraint = DefaultConstraint,
    Argument extends UserConstraint = UserConstraint
  > = Dispatcher<Argument>;

  const foo: ConstrainedDispatcher = (arg) => {
    const { name } = arg;
  };

  interface MyConstaint extends DefaultConstraint {
    lastName: string;
  }

  const bar: ConstrainedDispatcher<MyConstaint> = (arg) => {
    const { name, lastName } = arg;
  };
}
