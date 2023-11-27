// do more...
// - generate rgb graph
// - solving coloring problem
// - practice graph thing from graph.txt

#include <bits/stdc++.h>

/*

provided amount of test cases, edges and vertices, calculate the most optimal
price to color the buildings, each vertex represents a building and each
building has to be colored, each color has a price, pick colors so all the
buildings are colored in a way that yields the cheapest price

constraints
1 <= t <= 10
1 <= e < n <= 100.000
colors = 3
red green blue - in that order provided in input
only three colors for each vertex, first color is red, second color is green,
third color is blue two adjacent buildings can not have the same color, for
example an edge connects vertices 1 and 2, vertex 1 red, vertex 2 color may be
green or blue an edge connects vertices 1 and 2, vertex 1 green, vertex 2 color
may be red or blue an edge connects vertices 1 and 2, and 1 to 3, vertex 1 color
red, that means vertices 2 and 3 may pick between green or blue an edge connects
vertices 1 and 2, 2 and 3, vertex 1 color blue, vertex 2 color red, vertex 3
green or blue

the first line of input is t, for test cases followed by test cases
the first line of the test case has e, v where e is the amount of edges and v is
the amount of vertices that is followed by e amount of edges represented as
integers separated by one space that is followed by v amount of vertices, each
integer is a number representing a vertex in a graph where first integer
represent vertex followed by three digits representing price to color a building
with the color, for example 1 2 4 3 represents vertex 1 with color weights
red=2, green=4, blue=3 the output is an integer which represents the most
optimal price to color the buildings in the graph graph is undirected

input
1
1 2
1 2
1 1 2 3
2 4 5 6
output
6
explanation
the most optimal price to color building is to pick
red=1 for edge 1
green=5 for edge 2

input
2
2 3
1 2
2 3
1 1 2 3
2 4 5 6
3 7 8 9
1 2
1 2
1 1 1 1
2 1 1 1
output
13
2
explanation
the most optimal price to color buildings is to pick
red=1 for edge 1
green = 5 for edge 2
red = 7 for edge 3
the most optimal price to color buildings for test two is any of the colors as
all yield 2

input
1
1 2
1 2
1 1 3 4
2 1 10 10
output
4
explanation
the most optimal price to color buildings is to pick
green = 3 for edge 1
red = 1 for edge 2

input
1
2 3
1 2
1 3
1 3 1 4
2 1 5 8
3 3 2 4
output
5
explanation
vertex 1, green = 1
vertex 2, red = 1
vertex 3, red = 1
vertex 3 is adjacent to vertex 1 and can't pick cheapest green=2

*/

/*

once i startes thinking if the coloring graph problem is similar to coin change
problem, as well as my yesterday observation that recursive repetition is by
choosing the cheapest out of previous and current combinations,

r g
r b
g r
g b
b r
b g

previous r with current g
previous r with current b
previous g with currebt r
...

choose the cheapest of those

i was drawing choices yesterday and realized that there is repetitive choice on
each node

i was thinking about magus carlsen and how he knows who played a game in which
year by looking at the board, he played against 10 great chess players and won,
without looking, i also remembered the story of anders ericson and steve faloon
and how steve utilized long term memory which has no limits to remember
sequences of digits recited at him, i started thinking how can i utilize long
term memory to solve algorithmic problems that i dont know how to solve right
away, if i can utilize long term memory to map unfamiliar problems to familiar
ones and use technique to solve them then i can be better solver, however i need
to have a lot stored ij long term memory

*/

void solve() {
  int edges;
  int vertices;

  std::cin >> edges >> vertices;

  std::vector<std::vector<bool>> graph(edges, std::vector<bool>(edges, false));
  std::vector<std::array<int, 3>> vertex_weights(vertices);

  // Collect edges
  while (edges-- > 0) {
    int vertex_a;
    int vertex_b;

    std::cin >> vertex_a >> vertex_b;

    // To indices.
    --vertex_a;
    --vertex_b;

    graph[vertex_a][vertex_b] = true;
    graph[vertex_b][vertex_a] = true;
  }

  // Collect vertices
  while (vertices-- > 0) {
    int vertex;
    int red;
    int green;
    int blue;

    std::cin >> vertex >> red >> green >> blue;

    --vertex;  // To index.
    vertex_weights[vertex] = {red, green, blue};
  }

  for (auto itr{graph.begin()}; itr != graph.end(); ++itr) {
    for (auto jtr{itr->begin()}; jtr != itr->end(); ++jtr) {
      std::cout << std::distance(graph.begin(), itr) << " : "
                << std::distance(itr->begin(), jtr) << " = " << *jtr << " ";
    }
    std::cout << "\n";
  }

  for (auto itr{vertex_weights.begin()}; itr != vertex_weights.end(); ++itr) {
    for (auto jtr{itr->begin()}; jtr != itr->end(); ++jtr) {
      std::cout << std::distance(vertex_weights.begin(), itr) << " : "
                << std::distance(itr->begin(), jtr) << " = " << *jtr << " ";
    }
    std::cout << "\n";
  }
}

int main() {
  int tests;
  std::cin >> tests;

  while (tests-- > 0) {
    solve();
  }

  return 0;
}
