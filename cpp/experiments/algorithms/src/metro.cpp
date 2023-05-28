#include <bits/stdc++.h>
using namespace std;

// https://codeforces.com/problemset/problem/1055/A

bool solve(int n, int s, vector<int> &ft, vector<int> &st) {
  if (ft[0]) {
    if (ft[s - 1])
      return true;
    else if (st[s - 1]) {
      for (int i = s; i != n; ++i) {
        if (ft[i] && st[i]) return true;
      }
    }
  }
  return false;
}

int main() {
  int n, s;
  scanf("%d%d", &n, &s);
  vector<int> ft(n), st(n);
  for (int i = 0; i != n; ++i) {
    int b;
    scanf("%d", &b);
    ft[i] = (bool)b;
  }
  for (int i = 0; i != n; ++i) {
    int b;
    scanf("%d", &b);
    st[i] = (bool)b;
  }

  if (solve(n, s, ft, st))
    printf("YES");
  else
    printf("NO");

  return 0;
}
