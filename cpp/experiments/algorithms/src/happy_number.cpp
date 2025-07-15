#include <iostream>
#include <set>
using namespace std;

// https://leetcode.com/problems/happy-number/

class Solution {
 public:
  set<int> cache;
  bool isHappy(int n) {
    if (n == 1) return true;
    // i am ashamed, if i have observed that a number would go down to itself,
    // or repeat itself it would mean repetition, i never even thought of that,
    // maybe i should assemble a list of various properties that i should check
    // or try out from all the algorithmic solutions and practice TOTAL_RECALL
    // technique using them however i feel quite ashamed that this solution uses
    // O(???) memory i would guess that it uses at least O(n) memory because it
    // depends on each recursive call to N and since if we get number 2, and it
    // just keeps going up...
    cout << n << " -> " << cache.count(n) << "\n";
    if (cache.count(n) > 0) return false;
    cache.insert(n);
    // take each digit of n
    // square each digit of n
    // repeat the process with the result
    // one issue, what if the process keeps repeating itself
    //   - there must be some properties of any number that's never going to
    //   decrease through repeated steps of this process, perhaps a mathematical
    //   formula or something else?

    int sum = 0;
    while (n > 0) {
      sum += (n % 10) * (n % 10);
      n /= 10;
    }
    return isHappy(sum);
  }
};

// 1. understand the problem statement on the first example input
// 2. what are various inputs that i will get
// 3. try to spot a pattern in input and output (up to you)

/*

192

1^2 + 9^2 + 2^2 = 999
9^2 + 9^2 + 9^2 = ???


192

1
2
3
4
5

10
11
12
13
14

123
124
126

1. one digit of each resulting number
  - extract a digit from a number, do it for each digit
    - square each digit and sum them
  - repeat the process for the result

- which numbers loop endlessly?
- can mathematical formula determine such a number?
- are there other properties that allow our algorithm to detect and stop?



2
2^2 = 4
4^2 = 16
1 + 6*6 = 37
3*3 + 7*7 = // it would be greath if i were doing math

-------------------------------------

i believe we can extract the two parts of problems solving
- i know conceptual solution
- i know how to code the conceptual solution

these two parts are combine-able, for example

- i don't know conceptual solution
- i know how to code the conceptual solution ( once i find it )

- i don't know conceptual solution
- i don't know how to code the conceptual solution ( even once i find it )

- i know conceptual solution
- i don't know how to code it

- i know conceptual solution
- i know how to code it

this is important because i frequently realize i have found the solution to
the problem, but have i really? i don't think so, for example
the other day i was solving:
https://leetcode.com/problems/all-possible-full-binary-trees/

and i thought, oh, alright, i see how the current tree level is generated,
we can use previously generated trees and build up on that, that's what
dynamic programming is good at, we can also use top-down or bottom-up technique

however i realized, wait, there's this case and i have no idea how to solve it

- conceptually
- i don't know can i code it ( once i find conceptual solution )

these algorithmic problems are quite challenging, they have a lot of subproblems
that arise in solving larger problems, and for me, at the current level,
most of them are very difficult to solve, they require a lot of my brain power,
even the smaller subproblems within larger problem

i wonder how did the more experienced problem solvers tackle this issue, i
should get a concrete example and see if anyone of people on leetcode can help
me out on how to approach that situation

i realized all of this as i tried to solve the happy number problem,
conceptually i wanted to split the number digit by digit, and i realized there
was a technique where i could divide a number or take a remainder using a % or
something like that however i couldn't quite remember how to do that so i would
obviously google it or maybe i would need to figure it out by myself

but that is so specific to that syntax and how remainder works and etc and that
really makes me wonder, when should i google? what if the whole subproblem that
i'm trying to solve is actually another algorithm? i can easily see how it can
take more than one year for a person to get better at solving problems like
these, but obviously would easily require more than 3 years to get really good

probably even more if such a person wants to be able to solve all of these
problems out of the head, such an... intriguing observation, however i probably
am not the first one to discover this observation

*/
