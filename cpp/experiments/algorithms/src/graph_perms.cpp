#include <bits/stdc++.h>

/*

Am I learning anything from this? I am trying out different approaches and
struggling to get the permutations on graph with three properties on each node,
however it's not working out for three days now. Am I learning anything from
that?

- one idea, pass the currently chosen color, base case picks the other two,
combine current with the rest
-

*/

namespace Solution {

using Permutation = std::unordered_map<int, int>;
using Permutation_And_Sum = std::pair<Permutation, int>;

std::vector<Permutation_And_Sum> Calculate_Graph_Permutations(
    const std::vector<std::vector<int>>& adj,
    std::vector<std::array<int, 3>>& colors) {
  std::unordered_set<int> visited;

  std::function<int(int, const Permutation&)> get_connected_vertex_color{
      [](int, const Permutation& permutation) { return 0; }};

  std::function<std::vector<Permutation_And_Sum>(int)> Graph_Permutations{
      [&](int vertex) {
        visited.insert(vertex);
        if (/* last vertex */) {
          std::vector<Permutation_And_Sum> permutations;
          for (int color : colors[vertex]) {
            Permutation permutation;
            permutation[vertex] = color;
            Permutation_And_Sum permutation_and_sum =
                make_pair(permutation, color);
            permutations.push_back(permutation_and_sum);
          }
          return permutations;
        } else {
          std::vector<Permutation_And_Sum> permutations;

          for (const int child_vertex : adj[vertex]) {
            if (!visited.count(vertex)) {
              for (const auto& permutation : Graph_Permutations(child_vertex)) {
                for (int color{0}; color < 3; ++color) {
                  // chose unpicked colors of vertex current one connects to
                  if (color !=
                      get_connected_vertex_color(vertex, permutation)) {
                    // copy the current permutation
                    // insert the current vertex to the permutation and it's
                    // current color pick increase the sum by the colors[vertex]
                    // insert the current permutation to the permutations
                  }
                }
              }
            }
          }

          return permutations;
        }
      }};
}

}  // namespace Solution

int main() {
  int e, v;
  std::cin >> e >> v;

  std::vector<std::vector<int>> adj(v + 1);
  std::vector<std::array<int, 3>> w(v + 1);

  while (e-- > 0) {
    int a, b;
    std::cin >> a >> b;
    adj[a].push_back(b);
    adj[b].push_back(a);
  }

  while (v-- > 0) {
    int i;
    std::cin >> i >> w[i][0] >> w[i][1] >> w[i][2];
  }

  std::unordered_set<int> visited;
  std::vector<int> result;

  // std::function<void(int)> permute{[&](int vertex) {
  //   visited.insert(vertex);

  //   if (result.size() == 0) {
  //     for (int c : w[vertex]) {
  //       result.push_back(c);
  //     }
  //   } else {
  //     std::vector<int> new_result;
  //     for (int r : result) {
  //       new_result.push_back(r + w[vertex][]);
  //       new_result.push_back(r + w[vertex][]);
  //     }
  //     result = std::move(new_result);
  //   }

  //   for (int n : adj[vertex]) {
  //     if (!visited.count(n)) {
  //       permute(n);
  //     }
  //   }
  // }};

  // permute(1);

  return 0;
}
