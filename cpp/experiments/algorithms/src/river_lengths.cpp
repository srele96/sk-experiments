#include <bits/stdc++.h>
using namespace std;

/*

3
3 3
1 0 1
1 1 0
0 0 0
3 3
1 0 1
1 1 1
0 0 1
3 3
1 0 1
1 1 1
1 0 1

*/

/*

1 0 1 1
1 1 1 1

1 0 1 1 1
1 1 1 1 1

<0, 0>, <-1, -1>, <1, 2>
<0, 0>, <0, 0>, <0, 0>
<0, 0>, <-1, -1>, <0, 0>

7, 0, 0
0, 0, 0
0, 0, 0

This will not work. The poor amount of techniques I have to solve algorithmic
problems is overwhelming. I can't come up with proper path and my solutions
often lead to even more complex ones. I decided that I wanted to store a
reference to the river. Each cell references the part of which river it is. Each
cell references the begin of the river. However I did not see a case where
without updating references it is not possible to continue easily. Observe the
case:

1 0 1 1 1
1 1 1 1 1

[0, 0], [-1, -1], [0, 2], [0, 2], [0, 2]
[0, 0], [ 0,  0], [?, ?]

What now?

Somehow, whenever I choose to go down the route to solve a problem on my own, in
a different way, I oversee the complexity of the solution. I oversee that one
case that will fuck me up. The problem that I have encountered is that I don't
know how to proceed in that case.

Maybe before making a decision to proceed with a solution, I should look for
counter cases that my solution does not handle? That will spare me a lot of
pointless brain effort. I think.

I have thoughts on studying the techniques on algorithms invented by experts and
figure out ways and train my mind to come up with them. I would for days try to
reproduce the solution that they invented. In case I can not come up with that
solution after days, I would look it up, analyse it deeply for another day, two,
or more, find more similar problems and try to figure out solution in the
similar fashion to the way experts have come up with theirs. Currently without
an example of how to solve this problem, I don't have that fashion to exercise
thinking like experts and I fail to train my mind to come up with novel
techniques and tricks like they invented for their algorithms. Look for the work
of experts, analyse it, train my mind to think and come up with solutions like
theirs. Also... The river problem might be more easily solvable using recursion.
However I am REALLY eager to solve it in the fashin that I started to use
currently.

*/

bool has_ref(const pair<int, int>& p) { return p.first >= 0 && p.second >= 0; }

void max_river(vector<vector<int>>& vec) {
  vector<vector<int>> rivs(vec.size(), vector<int>(vec[0].size()));
  vector<vector<pair<int, int>>> rivs_ref(
      vec.size(), vector<pair<int, int>>(vec[0].size(), make_pair(-1, -1)));
  int m = 0;
  for (int i = 0; i < vec.size(); ++i) {
    for (int j = 0; j < vec[i].size(); ++j) {
      if (vec[i][j] == 1) {
        if (i - 1 >= 0 && j - 1 >= 0) {
          auto lr = rivs_ref[i - 1][j];
          auto tr = rivs_ref[i][j - 1];
          if (has_ref(lr) && has_ref(tr)) {
            // ... What the fuck do I do here?
          } else if (has_ref(lr)) {
            rivs[lr.first][lr.second] += rivs[i][j];
            rivs_ref[i][j] = lr;
          } else if (has_ref(tr)) {
            rivs[tr.first][tr.second] += rivs[i][j];
            rivs_ref[i][j] = tr;
          } else {
            rivs[i][j] = vec[i][j] + rivs[i - 1][j] + rivs[i][j - 1];
            rivs_ref[i][j] = make_pair(i, j);
          }
        } else if (i - 1 >= 0) {
          auto p = rivs_ref[i - 1][j];
          if (has_ref(p)) {
            rivs[p.first][p.second] += rivs[i][j];
            rivs_ref[i][j] = p;
          } else {
            rivs[i][j] = vec[i][j] + rivs[i - 1][j];
            rivs_ref[i][j] = make_pair(i, j);
          }
        } else if (j - 1 >= 0) {
          auto p = rivs_ref[i][j - 1];
          if (has_ref(p)) {
            rivs[p.first][p.second] += rivs[i][j];
            rivs_ref[i][j] = p;
          } else {
            rivs[i][j] = vec[i][j] + rivs[i][j - 1];
            rivs_ref[i][j] = make_pair(i, j);
          }
        } else {
          rivs[i][j] = vec[i][j];
          rivs_ref[i][j] = make_pair(i, j);
        }
        m = max(rivs[i][j], m);
      }
    }
  }

  cout << "Max: " << m << "\n";

  for (int i = 0; i < rivs.size(); ++i) {
    for (int j = 0; j < rivs[i].size(); ++j) {
      cout << rivs[i][j] << " ";
    }
    cout << "\n";
  }

  for (int i = 0; i < rivs_ref.size(); ++i) {
    for (int j = 0; j < rivs_ref[i].size(); ++j) {
      cout << i << ", " << j << " => " << rivs_ref[i][j].first << ", "
           << rivs_ref[i][j].second << "\n";
    }
  }
}

void solve() {
  int n, m;
  cin >> n >> m;
  vector<vector<int>> vec(n, vector<int>(m));
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j) cin >> vec[i][j];

  max_river(vec);
}

int main() {
  int t;
  cin >> t;
  while (t-- > 0) solve();

  return 0;
}
