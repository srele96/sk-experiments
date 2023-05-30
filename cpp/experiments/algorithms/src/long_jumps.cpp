#include <bits/stdc++.h>
using namespace std;

// https://codeforces.com/problemset/problem/1472/C

void solve() {
  int n;
  scanf("%d", &n);

  vector<int> a(n);
  for (int &i : a) {
    scanf("%d", &i);
  }

  vector<int> dp(n, -1);
  for (int i = n - 1; i >= 0; --i) {
    int sum = 0;
    int j = i;
    while (j < n) {
      if (dp[j] < 0) {
        sum += a[j];
        j += a[j];
      } else {
        sum += dp[j];
        j += dp[j];
      }
    }
    dp[i] = sum;
  }
  printf("%d\n", *max_element(dp.begin(), dp.end()));
}

int main() {
  int t;
  scanf("%d", &t);
  while (t-- > 0) solve();

  return 0;
}
