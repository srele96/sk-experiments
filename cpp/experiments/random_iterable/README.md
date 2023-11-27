# Random Iterable

A C++ iterable container that iterates over random elements and erases them. The container is empty when all elements have been iterated over.

## The problem statement

```txt
let's say that i have a collection of items where I want to select one random
item and remove it, each time iterator accesses an element I want to select one
and remove it from valid selections and it goes on until there are no more
elements

the user wouldn't know that as he would do something like

for (auto value : random_iterator<T>) {
  // use value
}

the type T should be storable in that pool, the pool could be a set of items
therefore T should be storable within a c++ set and I should be able to
retrieve random value from that set
```
