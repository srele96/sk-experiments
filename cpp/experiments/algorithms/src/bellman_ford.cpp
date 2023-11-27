#include <bits/stdc++.h>
using namespace std;

/*

The study of the Bellman-Ford algorithm.
https://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm


These algorithms somehow "magically just handle a lot of cases...". I
realized that bellman-ford algorithm takes in the source and I can set the
source to be any valid vertex within a graph and the algorithm will work?

That makes me wonder, when solving algorithmic problems and think:
"Oh! How do I solve that problem as well?"
Is there a better way to handle such "clicks"? The Bellman-Ford algorithm
looks so clean...!

*/

/*

Below is the input which verifies that my implementation works on a graph with
negative cycle and others.

*/

/*

6

3 4 1
1 2 5
2 3 3
1 4 2

3 4 2
1 2 5
2 3 3
1 4 2

3 4 3
1 2 5
2 3 3
1 4 2

3 4 4
1 2 5
2 3 3
1 4 2

10 5 1
1 2 6
1 3 7
2 3 8
2 4 5
2 5 -4
3 4 -3
3 5 9
4 2 -2
5 4 7
5 1 2

3 3 1
1 2 1
2 3 1
3 1 -3

*/

const int INF = numeric_limits<int>::max();
const int NONE = -1;

void bellman_ford(vector<vector<int>>& g, const int s) {
  int l = g.size();
  vector<int> d(l);
  vector<int> p(l);

  // Initialize
  for (int v = 1; v < l; ++v) {
    d[v] = INF;
    p[v] = NONE;
  }

  d[s] = 0;

  // relaxation
  for (int i = 1; i < l - 1; ++i) {
    for (int k = 1; k < l; ++k) {
      for (int o = 1; o < l; ++o) {
        if (g[k][o] != INF) {
          if (d[k] + g[k][o] < d[o]) {
            d[o] = d[k] + g[k][o];
            p[o] = k;
          }
        }
      }
    }
  }

  // Check for negative-weight cycles
  for (int i = 1; i < l; ++i) {
    for (int j = 1; j < l; ++j) {
      if (g[i][j] != INF) {
        if (d[i] + g[i][j] < d[j]) {
          p[j] = i;

          // negative cycle exists; find a vertex on the cycle
          vector<int> visited(l, false);
          visited[j] = true;

          int va = i;
          while (!visited[va]) {
            visited[va] = true;
            va = p[va];
          }

          vector<int> n_cycle{va};
          int vb = p[va];
          while (vb != va) {
            n_cycle.insert(n_cycle.begin(), vb);
            vb = p[vb];
          }

          cerr << "Graph contains a negative-weight cycle: ";
          for (const int v : n_cycle) {
            cout << v << " ";
          }
          cout << "\n";
        }
      }
    }
  }

  cout << "Distances from " << s << ":\n";
  for (int i = 1; i < l; ++i) {
    cout << "(V = " << i << ", D = " << d[i] << ") ";
  }
  cout << "\n";

  cout << "Predecessors:\n";
  for (int i = 1; i < l; ++i) {
    cout << "(V = " << i << ", P = " << p[i] << ") ";
  }
  cout << "\n";
}

void solve() {
  int e, v, s;
  cin >> e >> v >> s;
  int l = v + 1;
  vector<vector<int>> g(l, vector<int>(l, INF));

  while (e-- > 0) {
    int a, b, w;
    cin >> a >> b >> w;
    g[a][b] = w;
  }

  bellman_ford(g, s);
}

int main() {
  int t;
  cin >> t;

  while (t-- > 0) {
    solve();
  }

  return 0;
}
