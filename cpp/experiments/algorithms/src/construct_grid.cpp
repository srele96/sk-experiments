#include <bits/stdc++.h>
using namespace std;

/*

0,0

*/

namespace DP {

class Solution {
 public:
  vector<int> n;

  vector<int> f(const int i) {
    if (i >= n.size()) return {0};
    auto r = f(i + 1);
    r.push_back(n[i] + r[r.size() - 1]);
    return r;
  }

  vector<int> solve(vector<int>& nums) {
    n = move(nums);
    return f(0);
  }
};

}  // namespace DP

class Solution {
 public:
  int n;

  // matrix ...
  // matrix ...
  // matrix ...
  // matrix ...
  // matrix ...
  // matrix ...
  // matrix ...

  vector<vector<int>> f(const int i, const int j) {
    if (i < 0) return {};

    if (j >= 0) {
      auto r = f(i, j - 1);
      r[r.size() - 1].push_back(i * n + j);
      return r;
    }

    auto r = f(i - 1, n);
    r.push_back({});
    return r;
  }

  void solve(int _n) {
    n = _n - 1;
    const auto r = f(n, n);
    cout << "Result:\n\n";
    for (const auto& row : r) {
      for (const auto& col : row) {
        cout << col << ", ";
      }
      cout << "\n";
    }
  }
};

int f(const int n, vector<int>& v) {
  if (n < 0) return 0;
  cout << n << "\n";
  v[n] = n + f(n - 1, v);
  v[n - 1] = f(n - 1, v);
  return max(v[n], v[n - 1]);
}

namespace TryBetterDP {

class Solution {
 public:
  vector<unordered_set<int>> dp;

  void sth(const vector<int>& n, const int i = 0, const int s = 0) {
    if (dp[i].count(s)) {
      // cout << "Exist: " << i << ", " << s << "\n";
      return;
    }

    dp[i].insert(s);
    // cout << i << ", " << s << "\n";

    if (i == n.size()) return;

    sth(n, i + 1, n[i] + s);
    sth(n, i + 1, s);
  }

  void solve(vector<int>& n) {
    dp.resize(n.size() + 1);
    // cout << dp.size() << "\n";
    sth(n);
  }
};

}  // namespace TryBetterDP

namespace TryNotDp {

class Solution {
 public:
  vector<int> n;

  int f(int i) {
    if (i >= n.size()) return 0;
    return n[i] + f(i + 1);
  }

  vector<int> v(int i) {
    if (i >= n.size()) return {};
    auto r = v(i + 1);
    r.insert(r.begin(), f(i));
    return r;
  }

  vector<int> solve(vector<int>& _n) {
    n = move(_n);

    return v(0);
  }
};

}  // namespace TryNotDp

// n and sum of the rest
// sum of the rest

int main() {
  const int n = 3;
  Solution{}.solve(n);

  cout << "--------------\n";

  {
    vector<int> vec{5, 4, 3, 2, 1};
    for (const auto v : DP::Solution{}.solve(vec)) {
      cout << v << ", ";
    }
    cout << "\n";
  }

  cout << "----------------\n";

  // vector<int> v = vector<int>(2);
  // cout << f(v.size(), v) << "\n";
  // for (const int val : v) {
  //   cout << val << ", ";
  // }

  {
    vector<int> vec{1, 2, 3, 4, 5};
    TryBetterDP::Solution{}.solve(vec);
  }

  cout << "----------------\n";

  {
    vector<int> vec{1, 2, 3, 4, 5};
    for (const auto v : TryNotDp::Solution{}.solve(vec)) {
      cout << v << ", ";
    }
  }

  return 0;
}
