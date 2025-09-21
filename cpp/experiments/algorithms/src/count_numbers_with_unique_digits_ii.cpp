#include <bits/stdc++.h>
using namespace std;

// https://algo.monster/liteproblems/3032

class Solution {
 public:
  int unique(int a, int b) {
    unordered_map<string, pair<unordered_set<int>, bool>> dp;
    function<void(vector<int>&, int)> f{[&](vector<int>& d, int n) {
      if (n < 0) return;

      string prev = "";
      for (int i = n - 1; i >= 0; --i) prev += to_string(d[i]);
      string cur = to_string(d[n]) + prev;

      // For whatever reason, this shit has to be here
      if (dp.find(cur) != dp.end()) {
        return;
      }

      if (n == 0) {
        string k = to_string(d[n]);
        dp[k].first.insert(d[n]);
        dp[k].second = true;
        return;
      }
      if (n == 1) {
        string k = to_string(d[n]) + to_string(d[n - 1]);
        dp[k].first.insert(d[n - 1]);
        dp[k].first.insert(d[n]);
        dp[k].second = dp[k].first.size() == 2;
        return;
      }

      f(d, n - 1);

      dp[cur].first = dp[prev].first;
      dp[cur].first.insert(d[n]);
      dp[cur].second = dp[prev].second && dp[prev].first.count(d[n]) == 0;
    }};
    for (int i = a; i <= b; ++i) {
      vector<int> n;
      int r = i;
      while (r > 0) {
        n.emplace_back(r % 10);
        r /= 10;
      }
      // cout << "\n____\ni = " << i << "\n";
      // for (int v : n) cout << v << ", ";
      // cout << "\n";
      f(n, n.size() - 1);
    }
    // cout << "\n______________________\n";
    int c = 0;
    for (auto& [k, v] : dp) {
      // The algorithm caches for '109', dp['09'] as valid
      // Which is not valid for counting.
      if (v.second && k[0] != '0') {
        int s = stoi(k);
        // cout << "k=" << k << ", s=" << s << "\n";
        if (a <= s && s <= b) {
          ++c;
        }
      }
    }
    // cout << "____\nc=" << c << "\n";
    return c;
  }
};

/**
 * @brief Source of validation
 * https://leetcode.ca/2024-02-12-3032-Count-Numbers-With-Unique-Digits-II/
 */
namespace validateUsingCopiedSolutionFromTheInternet {

class Solution {
 public:
  int numberCount(int a, int b) {
    string num = to_string(b);
    int f[num.size()][1 << 10];
    memset(f, -1, sizeof(f));
    function<int(int, int, bool)> dfs = [&](int pos, int mask, bool limit) {
      if (pos >= num.size()) {
        return mask ? 1 : 0;
      }
      if (!limit && f[pos][mask] != -1) {
        return f[pos][mask];
      }
      int up = limit ? num[pos] - '0' : 9;
      int ans = 0;
      for (int i = 0; i <= up; ++i) {
        if (mask >> i & 1) {
          continue;
        }
        int nxt = mask == 0 && i == 0 ? 0 : mask | 1 << i;
        ans += dfs(pos + 1, nxt, limit && i == up);
      }
      if (!limit) {
        f[pos][mask] = ans;
      }
      return ans;
    };

    int y = dfs(0, 0, true);
    num = to_string(a - 1);
    memset(f, -1, sizeof(f));
    int x = dfs(0, 0, true);
    return y - x;
  }
};

}  // namespace validateUsingCopiedSolutionFromTheInternet

int main() {
  vector<pair<int, int>> c{{1, 20},     {100, 110}, {110, 120}, {120, 130},
                           {130, 140},  {140, 150}, {150, 160}, {190, 200},
                           {100, 200},  {200, 210}, {1, 1000},  {200, 300},
                           {900, 1000}, {1, 100},   {1, 200}};
  for (auto& [a, b] : c) {
    cout << "a=" << a << ", b=" << b << ", result=" << Solution{}.unique(a, b)
         << ", expect="
         << validateUsingCopiedSolutionFromTheInternet::Solution{}.numberCount(
                a, b)
         << "\n";
  }

  return 0;
}
