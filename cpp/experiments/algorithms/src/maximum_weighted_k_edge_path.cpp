#include <functional>
#include <iostream>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

namespace firstWorkingCacheableSolution {

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

    for (auto& edge : edges) {
      int u = edge[0], v = edge[1], w = edge[2];
      if (nodes[u] == nullptr) {
        nodes[u] = new Node{u};
      }
      if (nodes[v] == nullptr) {
        nodes[v] = new Node{v};
      }
      nodes[u]->children.push_back({w, nodes[v]});
    }

    vector<vector<unordered_map<int, pair<int, int>>>> dp(
        n, vector<unordered_map<int, pair<int, int>>>(k));

    function<pair<int, int>(Node*, int, int)> f = [&](Node* n, int c,
                                                      int e) -> pair<int, int> {
      if (n == nullptr) return {c, e};
      if (n->children.empty()) return {c, e};
      // Missed case
      if (e == k) return {c, e};

      if (dp[n->val][e].count(c)) {
        return dp[n->val][e][c];
      }

      int maxSum = -1;
      int edges = e;
      for (auto& child : n->children) {
        auto res = f(child.second, child.first + c, e + 1);

        if (res.first < t && res.second == k) {
          maxSum = max(maxSum, res.first);
          edges = res.second;
        }
      }
      return dp[n->val][e][c] = {maxSum, edges};
    };

    int maxSum = -1;
    for (int i = 0; i < n; ++i) {
      const auto res = f(nodes[i], 0, 0);
      if (res.first < t && res.second == k) {
        maxSum = max(maxSum, res.first);
      }
    }

    return maxSum;
  }
};

}  // namespace firstWorkingCacheableSolution

namespace cacheOnlyByVertexAndEdge_SOLUTION_DOES_NOT_WORK {

struct Node {
  int val;
  vector<pair<int, Node*>> children;
};

/**
 * Working through this problem made me realize how accumulating through
 * parameters and returning accumulated values at the recursive base case can
 * affect solutions.
 * Pruning the branches becomes easy because at the parent of leaf nodes we know
 * the whole decision tree up to that node and we can decide what to do with the
 * two child leaf nodes.

DAG - Directed acyclic  graph

edges = [[0,1,10],[0,2,1],[1,3,1],[2,3,1],[3,4,10],[3,5,2]]
where: e[0] - fromVertex, e[1] - toVertex, e[2] - weight
where: [0, 1, 10] fromVertex=0, toVertex=1, weight=10

      0
    /   \
   1     2
    \   /
      3
   /    \
  5      4

if we start from 0, and accumulate edges, if we do 0, 1, 3, 4, then return at
base case, we have at edge 3 result of:

3-5: edges=3, weight=13
3-4: edges=3, weight=21

i find it amusing that challenging myself by wishing to avoid accumulatedSum as
a cacheKey to achieve a higher form of understanding of a problem
that's miraculous and spectacular, absolutely amazing
 */

class Solution {
 public:
  int maxWeight(int n, vector<vector<int>>& edges, int k, int t) {
    // Missed case
    if (edges.empty()) {
      return k > 0 ? -1 : 0;
    }

    vector<Node*> nodes(n, nullptr);

    for (auto& edge : edges) {
      int u = edge[0], v = edge[1], w = edge[2];
      if (nodes[u] == nullptr) {
        nodes[u] = new Node{u};
      }
      if (nodes[v] == nullptr) {
        nodes[v] = new Node{v};
      }
      nodes[u]->children.push_back({w, nodes[v]});
    }

    vector<vector<int>> dp(n, vector<int>(k, -1));

    // function<pair<int, int>(Node*, int)> f =[&](Node* n, int e) ->
    // pair<int,int> {
    //   if (n == nullptr) return {0, k - e};
    //   if (n->children.empty()) {
    //     return { 0, k - e};
    //   };
    //   if (e == 0) return {0, k - e};

    //   int maxSum = -1;
    //   int edges = -1;
    //   for(auto& child : n->children) {
    //     cout << child.first << "\n";
    //     auto [resSum, resEdges] = f(child.second, e - 1);
    //     cout << "child.first="<< child.first << ", resSum=" << resSum << ",
    //     maxSum=" << maxSum << ", resEdges="<< resEdges << "\n"; int r =
    //     child.first + resSum; cout << "r=" << r << "\n"; if (r < t && r >
    //     maxSum && resEdges == k) {
    //       maxSum = r;
    //       edges = resEdges;
    //     }
    //   }

    //   return {maxSum,edges};
    // };

    function<pair<int, int>(Node*, int)> f = [&](Node* n,
                                                 int e) -> pair<int, int> {
      if (n == nullptr) return {0, e};
      if (n->children.empty()) {
        return {0, e};
      };
      if (e == 0) return {0, e};

      int maxSum = -1;
      int edges = -1;
      for (auto& child : n->children) {
        auto [resSum, resEdges] = f(child.second, e - 1);
        resSum = child.first + resSum;
        if (resSum < t && resEdges == 0) {
          maxSum = max(maxSum, resSum);
          edges = resEdges;
        }

        // cout << child.first << "\n";

        // cout << "child.first="<< child.first << ", resSum=" << resSum << ",
        // maxSum=" << maxSum << ", resEdges="<< resEdges << "\n";
      }

      return {maxSum, edges};
    };

    int maxSum = -1;
    for (int i = 0; i < n; ++i) {
      cout << ">>>> I=" << i << "\n";
      auto [sum, edges] = f(nodes[i], k);
      cout << "i=" << i << ", maxSum=" << maxSum << ", sum=" << sum
           << ", edges=" << edges << "\n";
      if (sum < t && edges == 0) {
        maxSum = max(maxSum, sum);
      }
    }

    return maxSum;
  }
};

}  // namespace cacheOnlyByVertexAndEdge_SOLUTION_DOES_NOT_WORK

namespace topologicallySortedNodesAfterMuchEffort {
/*

I think after yesterday's analysis of the topologically sorted array of vertices
and analysis of algorithms execution, i came up with a great idea today.

I think the idea was not mine, but i saw it on the LeetCode briefly.

The idea of runtime of the algorithm being O(N*K*C).

The solution was to add in the for loop, iteration over all costs to reach the
given: dp[node][edges]

So the algorithm loop looks like:

for (int node : topologicallySortedNodes) {
  for(int edges = 0; edges < k; ++edges) {
    for(int cost : dp[node][edges]) {

      for(const auto& [child, weight] : graph[node][edges]) {

      }

    }
  }
}

I believe the idea is not mine because as I was skimming through the solutions
section I saw a nested loop with 3 for loops.

The problem i was encountering is that at dp[nodes] you have to be re-evaluating
the cost of edges because what is optimal choice now, may not be an optimal
choice later.

Also yesterday exercise of visualization of how the algorithm works, and being
able to describe each section of an algorithm for example;

for each node:
  for each edgeCount from 0 to k:
    for each parentWeight in dp[node][edgeCount]:
      for each [child, weight]:
        childSum = weight + parentWeight
        if childSum < t:
          dp[child][edgeCount + 1] = childSum

And really being able to see the meaning of how it works over each edge and
being able to describe it as: at each node, go to its child, the path to child
is 1 edge more than to reach the parent, do it for edges from 0 to k

We do edges from 0 to k because for the next node, we have to start over, and
initially for any child, since we traverse in topological order, the child may
not have computed the sum for dp[child][1], so we have to start there.

And really being able to visualize the algorithm execution on a whim really
helped because the idea "what if i can iterate over all costs for curent
dp[node][edges]" really did strike me and it felt like that was it...

I also kinda learned the topological sort algorithm because i had to figure out
and understand how does this god damn thing work.

*/

class Solution {
 public:
  int maxWeight(int n, vector<vector<int>>& edges, int k, int t) {
    vector<int> indeg(n);
    vector<vector<pair<int, int>>> graph(n);
    for (auto& edge : edges) {
      int u = edge[0], v = edge[1], w = edge[2];
      ++indeg[v];
      graph[u].emplace_back(v, w);  // Bug, u instead of v
    }
    queue<int> q;
    vector<vector<unordered_set<int>>> dp(n, vector<unordered_set<int>>(k + 1));
    for (int i = 0; i < n; ++i) {
      // Bug, was inside if (indeg[i] == 0), should be outside
      dp[i][0].insert(0);
      if (indeg[i] == 0) {
        q.push(i);
      }
    }
    vector<int> topo;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      topo.emplace_back(u);
      for (auto& [v, w] : graph[u]) {
        if (--indeg[v] == 0) {
          q.push(v);
        }
      }
    }
    for (int u : topo) {
      for (int e = 0; e < k; ++e) {
        for (int c : dp[u][e]) {
          for (auto& [v, w] : graph[u]) {
            int r = c + w;
            if (r < t) {
              // Bug, used [u][e]
              dp[v][e + 1].insert(r);
            }
          }
        }
      }
    }
    int r = -1;
    for (int u : topo) {
      for (int c : dp[u][k]) {
        r = max(r, c);
      }
    }
    return r;
  }
};

}  // namespace topologicallySortedNodesAfterMuchEffort
