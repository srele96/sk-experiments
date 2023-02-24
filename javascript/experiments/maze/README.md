# Maze

I would like to generate a maze using an efficient algorithm.

## Purpose and usage of efficient algorithms and data structures

I have realized that algorithms aren't set in stone. I can use algorithms and data structures to fit them into my solution to the problem. For example, Kruskal's algorithm to generate a minimum spanning tree is suitable for creating mazes. While solving the problem I realized that I was using data for the two-dimensional context of JavaScript canvas. Using two-dimensional context, I generate a grid; to do that, I need some values required by the canvas application programming interface. Data to draw it using OpenGL is different, but Kruskal's algorithm time complexity and space complexity of these operations remain the same. It is up to me how I will use the algorithm to generate the minimum spanning tree. For example, whenever I connect two components, I should destroy a wall between them. I found a relatively small solution to "destroy" a wall; the solution requires the wall's position and size. The wall position can be placed on the edge, and whenever two components are connected, I can use values stored on the edge to remove the wall. The algorithms and data structures are among many programming tools I can use to write good, efficient, and performant programs.

## Stages

The maze generation started as an `index.html` but then I decided to use `webpack` to make code modular. The `index.html` contained around 400 lines of code and it looked like too much. I wanted to have better overview of code in each component without having to look at implementation for called procedures.

## Success Gallery

A collection of pictures after I completed the maze generation algorithm.

### One

![One](./asset/07.png)

### Two

![Two](./asset/08.png)

### Three

![Three](./asset/09.png)

### Four

![Four](./asset/10.png)

### Five

![Five](./asset/11.png)

### Six

![Six](./asset/12.png)

### Seven

![Seven](./asset/13.png)

## Gallery

A collection of pictures to remember how the process of maze creation went.

These pictures are before I completed the maze generation algorithm and experimentation stage.

### Five by Five Cells

![Five by Five Cells](./asset/01.png)

### Three by Three Cells

![Three by Three Cells](./asset/02.png)

### Seven by Seven Cells

![Seven by Seven Cells](./asset/03.png)

### Fifteen by Fifteen Cells

![Fifteen by Fifteen Cells](./asset/04.png)

### Ten by Ten Cells

![Ten by Ten Cells](./asset/05.png)

### Twenty by Twenty Cells

![Twenty by Twenty Cells](./asset/06.png)
