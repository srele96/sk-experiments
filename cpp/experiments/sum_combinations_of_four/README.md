# Combinations of four that matches sum

## Description

From the sample, find all combinations of four elements whose sum matches the one in parameter.

```c++
std::vector<std::vector<int>> get_combinations_of_four_that_match_sum(
    std::vector<int> sample, int sum)
```

## Problems with the implementation

The problem with the algorithm is that it is time and space complexity inefficient.

The inner-most loop contains combination, which means it creates an array pushes elements in and adds it to combinations

- A combination of 3 has 3 nested loops.
- A combination of 4 has 4 nested loops.

One benefit is that if we observe r as constant, where r=4 that reduces the algorithm runtime. However it still kind of depends on it's value.

The formula: n! / (r! \* (n - r)!)

Becomes: n! / (4! \* (n - 4)!)

That is good for us because in big O notation we "cancel" constants because they are "small" and "irelevant" compared to variable input size.

## My approach to the solution

See [algorithm combinations of four and sum](https://dev.to/srele96/algorithm-combinations-of-four-and-sum-4g29).
