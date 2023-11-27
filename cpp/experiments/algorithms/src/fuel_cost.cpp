#include <bits/stdc++.h>
using namespace std;

namespace dfs {

class Solution {
 public:
  long long fuel = 0;
  vector<vector<int>> adj;

  int dfs(int current_city, int parent_city, int seats) {
    int people = 1;

    for (const int neighbour_city : adj[current_city]) {
      if (neighbour_city != parent_city) {
        people += dfs(neighbour_city, current_city, seats);
      }
    }

    if (current_city > 0) {
      fuel += (people + seats - 1LL) / seats;
    }

    return people;
  }

  long long minimumFuelCost(vector<vector<int>>& roads, int seats) {
    adj.resize(roads.size() + 1);

    for (const auto& road : roads) {
      adj[road[0]].push_back(road[1]);
      adj[road[1]].push_back(road[0]);
    }

    dfs(0, -1, seats);

    return fuel;
  }
};

}  // namespace dfs

int main() {
  vector<vector<int>> roads{
      {0, 1},
      {0, 2},
      {0, 3},
  };
  int seats = 5;

  cout << dfs::Solution{}.minimumFuelCost(roads, seats);

  return 0;
}
