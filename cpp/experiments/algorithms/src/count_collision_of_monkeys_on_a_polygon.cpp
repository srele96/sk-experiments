#include <bits/stdc++.h>
using namespace std;

namespace inefficientTLE {

// Perfect. Exactly as I wanted. TLE.
// I translated my recursive solution into iterative.
// Solves the problem in O(n) time.
// Required solution is O(log(n)) time.
// I don't care about that because I don't want to understand mathematical
// problems at the moment. I want to go back to dynamic programming funsies.
class Solution {
 public:
  const int MOD = 1000000007;

  int monkeyMove(int n) {
    long long r = 2;
    for (int i = 0; i < n - 1; ++i) {
      r = (2LL * r) % MOD;
    }
    return (r - 2 + MOD) % MOD;
  }
};

}  // namespace inefficientTLE

namespace nonModular {

class Solution {
 public:
  int monkeyMove(int n) {
    function<int(int)> f = [&](int i) {
      if (i == 0) return 2;
      return 2 * f(i - 1);
    };
    return f(n - 1) - 2;
  }
};

}  // namespace nonModular
