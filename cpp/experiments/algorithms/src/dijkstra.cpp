#include <bits/stdc++.h>
using namespace std;

using pii = pair<int, int>;

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<pii>> graph(n);

  while (m--) {
    int a, b, w;
    cin >> a >> b >> w;
    a = a - 1;
    b = b - 1;
    graph[a].push_back(make_pair(w, b));
    graph[b].push_back(make_pair(w, a));
  }
  vector<int> dists(n, numeric_limits<int>::max());
  vector<bool> vis(n, false);
  vector<int> prev(n);

  priority_queue<pii, vector<pii>, greater<pii>> pq;
  pq.push(make_pair(0, 0));
  dists[0] = 0;

  bool p_f = false;
  while (!pq.empty()) {
    auto top = pq.top();
    pq.pop();

    vis[top.second] = true;
    if (top.second == n - 1) p_f = true;

    for (auto &nb : graph[top.second]) {
      if (!vis[nb.second]) {
        int dist = top.first + nb.first;
        if (dist < dists[nb.second]) {
          dists[nb.second] = dist;
          pq.push(make_pair(dist, nb.second));
          prev[nb.second] = top.second;
        }
      }
    }
  }
  if (p_f) {
    int pr = n - 1;
    vector<int> pth;
    while (pr != 0) {
      pth.push_back(pr);
      pr = prev[pr];
    }
    pth.push_back(0);
    for_each(pth.rbegin(), pth.rend(), [](auto &v) { cout << v + 1 << " "; });
  } else {
    cout << -1;
  }

  return 0;
}
