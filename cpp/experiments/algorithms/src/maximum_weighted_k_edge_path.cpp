#include <vector>
#include <unordered_map>
#include <utility>
#include <functional>
using namespace std;

struct Node {
  int val;
  vector<pair<int, Node*>> children;
};

class Solution {
public:
  int maxWeight(int n, vector<vector<int>>& edges, int k, int t) {
    // Missed case
    if (edges.empty()) {
      return k > 0 ? -1 : 0;
    }

    vector<Node*> nodes(n, nullptr);

    for(auto& edge : edges) {
      int u = edge[0], v = edge[1], w = edge[2];
      if (nodes[u] == nullptr) {
        nodes[u] = new Node{u};
      }
      if (nodes[v] == nullptr) {
        nodes[v] = new Node{v};
      }
      nodes[u]->children.push_back({w, nodes[v]});
    }

    vector<vector<unordered_map<int,pair<int, int>>>> dp(
      n,
      vector<unordered_map<int, pair<int, int>>>(k)
    );

    function<pair<int, int>(Node*, int, int)> f =[&](Node* n, int c, int e) -> pair<int, int> {
      if (n == nullptr) return {c, e};
      if (n->children.empty()) return {c, e};
      // Missed case
      if (e == k) return {c, e};

      if (dp[n->val][e].count(c)) {
        return dp[n->val][e][c];
      }

      int maxSum = -1;
      int edges = e;
      for(auto& child : n->children) {
        auto res = f(child.second, child.first + c, e + 1);

        if (res.first < t && res.second == k) {
          maxSum = max(maxSum, res.first);
          edges = res.second;
        }
      }
      return dp[n->val][e][c] = { maxSum, edges };
    };

    int maxSum = -1;
    for(int i = 0; i < n; ++i) {
      const auto res = f(nodes[i], 0, 0);
      if (res.first < t && res.second == k) {
        maxSum = max(maxSum, res.first);
      }
    }

    return maxSum;
  }
};
