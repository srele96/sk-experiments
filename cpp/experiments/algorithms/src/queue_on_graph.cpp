#include <bits/stdc++.h>

/*

The first line of input is the amount of test cases t.
Second like is two integers edges e and vertices v.
Followed by edges e which are pairs of vertices that edge connects.

For example, 1 test case, followed by 2 edges and 3 vertices.

1
2 3
1 2
1 3

Or

2
1 2
1 2
4 5
1 2
2 3
1 4
1 5

*/

void solve() {
  int edges;
  int vertices;

  std::cin >> edges >> vertices;

  const int length = vertices + 1;
  std::vector<std::vector<bool>> adj_matrix(length,
                                            std::vector<bool>(length, false));

  while (edges-- > 0) {
    int vertex_a;
    int vertex_b;

    std::cin >> vertex_a >> vertex_b;

    adj_matrix[vertex_a][vertex_b] = true;
    adj_matrix[vertex_b][vertex_a] = true;
  }

  struct BFS {
    std::vector<std::vector<bool>>& m_adj_matrix;

    BFS(std::vector<std::vector<bool>>& adj_matrix)
        : m_adj_matrix{adj_matrix} {}

    void solve() {
      std::unordered_set<int> visited;
      std::queue<int> q;
      q.push(1);

      while (!q.empty()) {
        int vertex = q.front();
        q.pop();
        visited.insert(vertex);

        std::cout << vertex << "\n";

        for (int i = 1; i < m_adj_matrix[vertex].size(); ++i) {
          if (m_adj_matrix[vertex][i] && !visited.count(i)) {
            q.push(i);
          }
        }
      }
    }
  };

  std::cout << "Breadth-First Search:\n";
  BFS{adj_matrix}.solve();
}

int main() {
  int tests;

  std::cin >> tests;

  while (tests-- > 0) {
    solve();
  }

  return 0;
}
