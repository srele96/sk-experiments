# Take parameter by reference in class constructor

What happens if the value mutates afterwards?

## Steps

1. I use constructor which is using constant reference to a type.
2. Then print the object's property.
3. Then mutate the value passed to the constructor.
4. Then print object's property again.

Since they use the same piece of memory, that can be dangerous.

## Result

Mutation outside of object didn't affect object's property. Why?

## Answer - I need to have a reference member

See [here](https://stackoverflow.com/questions/9507008/passing-by-reference-to-a-constructor).
