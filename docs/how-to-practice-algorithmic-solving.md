# How to practice algorithmic solving

A collection of advices, resources, examples, techniques, and thoughts I collected over time on how to learn and practice problem-solving.

**THESE ARE NOT RULES. USE AS GUIDELINES.**

**SPEND AT LEAST A MONTH ON EACH TECHNIQUE SOLVING VARIOUS PROBLEMS THAT CAN BE SOLVED USING IT.**

Come up with techniques that work for you. Use these notes as an idea of how to practice. Do whatever makes it comfortable for you to start practicing. Then keep pushing yourself outside of your comfort zone and **LEARN** then **PRACTICE** the technique learned.

- Read some part of [Competitive programming book](https://cses.fi/book/book.pdf). _(I didn't read it all. I've read some parts and practiced some as well. For example use minimum spanning tree Kruskal's algorithm to implement a maze using your favourite programming language. Not focused on algorithms, but helps see real world application of algorithms.)_

## Example

- how to bombard chatgpt with question about the topic one wishes to learn
  - [asking drilling questions about two pointers technique](https://github.com/srele96/how-to-practice-algorithmic-solving/tree/main/example/transform-problem.md)
  - [asking drilling questions to understand mathematical quaternions](https://github.com/srele96/how-to-practice-algorithmic-solving/tree/main/example/try-to-understand-quaternions/)
- [self-reflecting thoughts on how to practice algorithmic problem solving](https://github.com/srele96/how-to-practice-algorithmic-solving/tree/main/example/practice_algorithmic_solving.txt)
- [how to use conceptual thinking](https://github.com/srele96/how-to-practice-algorithmic-solving/tree/main/example/play_with_docker/)
- [create a problem for a (solution, techinique, or whatever you want to learn)](https://github.com/srele96/how-to-practice-algorithmic-solving/tree/main/example/create-problem-for-dp.md)

## Great reads

- [Do you think there is any value in software companies asking coding tests from candidates even after they have seen the resume?](https://qr.ae/pK881R)
- [What does a regret hire look like in Software Engineering?](https://qr.ae/pK888n)
- [Why patterns are important in algorithms, math, language, life, anything...](https://qr.ae/pK88T5)
- [Why do the majority of applicants never get contacted?](https://qr.ae/pK881W)
- [What is the path starting from 0 in programming to get very good at competitive programming?](https://qr.ae/pylUlM)
- [Why are competitive programmers looked down upon by software engineers?](https://qr.ae/pylUuM)
- [What is the skill that made you a productive programmer?](https://qr.ae/pK88RB)

## Learn a technique

**TRY TO THINK HARD TO FIGURE OUT THE DIFFERENCE BETWEEN LEARNING AND PROBLEM-SOLVING. THEY ARE DIFFERENT AND DIFFERENCE IN ALGORITHMIC PROBLEMS IS NOT OBVIOUS.**

Visit [tower of hanoi on wikipedia](https://en.wikipedia.org/wiki/Tower_of_Hanoi) and read the page.

**DO NOT READ THE CODE OF THE SOLUTION**.

Focus on the worded solution to the recursion, code never helps, for example:

If we have plates and three towers:

```txt
on current state of plates, tower_a, tower_b, tower_c
  if there are plates
    move plates - 1 from tower_a to tower_b // move all but last
    move plate from tower_a to tower_c
    move plates - 1 from tower_b to tower_c // move remaining towers
```

Or for example:

```txt
on a cell
  if i can move to right cell
    calculate right cell
    repeat for right cell
  if i can move to left cell
    calculate left cell
    repeat for left cell
  if i can move to up cell
    calculate up cell
    repeat for up cell
  if i can move to down cell
    calculate down cell
    repeat for down cell
```

Or for example:

```txt
on a node
  if a node is valid
    go to left child
    go to right child
```

Questions one can start from and expand from:

```txt
Why does recursion work?
How does recursion run?
How does solving the smallest recursive problem help figure out recursive solution?
How does using debugger help understand recursion?
How can I execute recursion on the paper?
How can I execute recursion in my thoughts?
Why does node left and right child algorithm work on any sized tree?
```

Tree:

```txt
  3
 / \
1   2
```

```txt

// structure of a node:

node:
  left
  right

// algorithm:

visit_tree(node):
  if node exists
    visit_tree(node.left)
    visit_tree(node.right)

// execution of the algorithm:

visit_tree(3):
  if 3 exists
    visit_tree(1) // execute
    visit_tree(2)

visit_tree(1):
  if 1 exists
    visit_tree(null) // execute
    visit_tree(null)

visit_tree(null):
  if null exists // doesnt exist
    visit_tree(null)
    visit_tree(null)
  // exit

// back to visit_tree(1)

visit_tree(1):
  if 1 exists
    visit_tree(null)
    visit_tree(null) // execute

visit_tree(null):
  if null exists // doesnt exist
    visit_tree(null)
    visit_tree(null)
  // exit

visit_tree(1):
  if 1 exists
    visit_tree(null)
    visit_tree(null)
    // done

// back to visit_tree(3)

visit_tree(3):
  if 3 exists
    visit_tree(1)
    visit_tree(2) // execute

visit_tree(2):
  if 2 exists
    visit_tree(null) // execute
    visit_tree(null)

visit_tree(null):
  if null exists // doesnt exist
    visit_tree(null)
    visit_tree(null)
  // exit

// back to visit_tree(2)

visit_tree(2):
  if 2 exists
    visit_tree(null)
    visit_tree(null) // execute

visit_tree(null):
  if null exists // doesnt exist
    visit_tree(null)
    visit_tree(null)
  // exit

// back to visit_tree(2)

visit_tree(2):
  if 2 exists
    visit_tree(null)
    visit_tree(null)
    // done ...
```

## Solve problems using the technique

Think about details:

- Why are constraints in the problem?
- Why are constraints important?
- Why is reading the problem statement important?
- Why is analysis of different inputs important?

How to solve:

- Read the whole problem statement.
- Think about different inputs that algorithm receives and what outputs should it produce for those inputs.
- Read the problem constraints such as `1 < N < 1000`
- Do I understand how the output looks for different inputs?

Try to think about the code and programming language as a tool.

I was thinking of how would i take the shortest route from the beach to the nearest supermarket. Around me were stairs and the city had a lot of stairs and uphill walk. Some stairs were crowded and appeared to have the shortest route, but were more uphill. Other stairs were longer, but the uphill climb was smaller. I could have taken the walk road around beaches until I saw some good stairs to climb to the nearest supermarket. I would need to figure out how to go to the supermarket calculating people, stairs, length, building placements, etc... How do I calculate the shortest path from my current location? That's conceptual solution. When solving and thinking about algorithmic problems, think conceptually. Once there is conceptual solution, translate it to the code.

Translating the conceptual solution to the code might be challenging, one example is:

```txt
For each stair around me
  calculate the distance to the supermarket
```

How are stairs represented? How do I calculate the distance? Is calculating the distance a formula such as `A - B` or some algorithmic procedure? How can I write placeholder algorithm calls to help me offload problem solving difficulty?

Observe some competitive programmers how they solve problems. Learn how do the best solve problems and try to reproduce what they do.
