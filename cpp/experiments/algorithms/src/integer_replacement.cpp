#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  // unordered_map<long long, int> dp;
  int solve(long long n) {
    // if (dp.count(n)) {
    //   return dp[n];
    // }
    if (n == 1) return 0;
    if (n % 2 == 0) {
      return 1 + solve(n / 2);
    } else {
      return 1 + min(solve(n + 1), solve(n - 1));
    }
  }

  int integerReplacement(int n) { return solve(n); }
};

namespace InitialIdea {

/*
I made a wrong assumption that i need `op` parameter to hold operations.
I could have just used `1 + solve(n / 2)` where 1 anotates the operation applied
The base case can return 0 as a neutral catalyst which can be summed up...

Why in the world does this beats 100% runtime and 60.52% memory? Based on
what...
*/
class Solution {
 public:
  int solve(long long n, int op) {
    if (n == 1) return op;
    if (n % 2 == 0) {
      return solve(n / 2, op + 1);
    }
    return min(solve(n + 1, op + 1), solve(n - 1, op + 1));
  }
  int integerReplacement(int n) { return solve(n, 0); }
};

}  // namespace InitialIdea
namespace BetterIdea {

class Solution {
 public:
  unordered_map<long long, int> dp;
  int solve(long long n) {
    if (dp.count(n)) return dp[n];
    if (n == 1) return dp[n] = 0;
    if (n % 2 == 0) {
      return dp[n] = 1 + solve(n / 2);
    } else {
      return dp[n] = 1 + min(solve(n + 1), solve(n - 1));
    }
  }

  int integerReplacement(int n) { return solve(n); }
};

}  // namespace BetterIdea
