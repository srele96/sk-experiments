#include <bits/stdc++.h>

// no clue if correct

int main() {
  int e;
  int v;
  std::cin >> e >> v;

  std::vector<std::vector<int>> adj(v);
  std::vector<std::array<int, 3>> colors(v);

  for (int i{0}; i < e; ++i) {
    int v_a;
    int v_b;

    std::cin >> v_a >> v_b;

    adj[--v_a].push_back(--v_b);
  }

  std::cout << "Vertices:\n";
  for (auto& row : adj) {
    for (auto c : row) {
      std::cout << c << " ";
    }
    std::cout << "\n";
  }

  for (int i{0}; i < v; ++i) {
    int vertex;
    constexpr int red = 0;
    constexpr int green = 1;
    constexpr int blue = 2;

    std::cin >> vertex;
    --vertex;
    std::cin >> colors[vertex][red] >> colors[vertex][green] >>
        colors[vertex][blue];
  }
  std::cout << "Colors:\n";
  for (auto& row : colors) {
    for (auto color : row) {
      std::cout << color << " ";
    }
    std::cout << "\n";
  }

  std::vector<std::pair<std::unordered_map<int, int>, int>> permutations;

  std::function<void(int)> permute{[&](int vertex) {
    if (permutations.size() < 3) {
      for (int color{0}; color < 3; ++color) {
        std::unordered_map<int, int> m;
        m[vertex] = color;
        std::pair<std::unordered_map<int, int>, int> p =
            std::make_pair(std::move(m), colors[vertex][color]);
        permutations.push_back(p);
        std::cout << vertex << " " << p.first[vertex] << " " << p.second
                  << "\n";
      }
    } else {
      std::vector<std::pair<std::unordered_map<int, int>, int>> tmp;
      for (auto& pair : permutations) {
        for (int color{0}; color < 3; ++color) {
          if (pair.first[vertex] != color) {
            std::cout << vertex << " " << color << " " << pair.first[vertex]
                      << " " << pair.second << "\n";
          }
        }
      }
    }

    for (int child : adj[vertex]) {
      permute(child);
    }
  }};

  std::cout << "\n";

  permute(0);

  for (const auto& pair : permutations) {
    for (const auto& val : pair.first) {
      std::cout << "v = " << val.first << ", color = " << val.second << "\n";
    }
    std::cout << "Sum = " << pair.second << "\n";
  }

  return 0;
}

/*

3 4
1 2
1 3
2 4
1 1 2 3
2 1 2 3
3 1 2 3
4 1 2 3

*/
