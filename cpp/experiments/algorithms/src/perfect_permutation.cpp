#include <bits/stdc++.h>
using namespace std;

// https://codeforces.com/problemset/problem/233/A
int main() {
  int n;
  cin >> n;
  // If n is odd, then there is no solution
  if (n % 2 != 0) {
    cout << -1;
  } else {
    // for 1 print 2 then 1
    // for 3 print 4 and 3
    // for 5 print 6 and 5
    // etc...
    for (int i = 1; i <= n; i += 2) {
      cout << i + 1 << " " << i << " ";
    }
  }
}
