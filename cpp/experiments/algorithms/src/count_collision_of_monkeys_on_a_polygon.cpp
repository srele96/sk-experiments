#include <bits/stdc++.h>
using namespace std;

namespace FastPow {

/*
First of, the two are supposedly the same:

(r - 2 + m) mod m
(r - 2) mod m

I googled to understand this property:

"if a ≡ b (mod m) then a + m ≡ b (mod m)"

From where I got proof of congruence property.

The reason we need to add modulo is because (r-2) might be negative.

-------------------------------------------------------------------------------

Then, the fast POW:

if n=2k: x^n = (x^2)^(n/2)
else x^n = x*(x^2)^((n-1)/2)

From where we get:

int n = ?
long long r = 1, x = 2;
while(n > 0) {
  if (n & 1) r *= x;
  x *= x;
  n >>= 1;
}

Where does (n-1) disappear? - It does not. It is there.
  [3/2 = 1] == [(3-1)/2 = 1].

Why `if (n & 1)` to check oddity of number? Binary representation:
  0000 = 0
  0001 = 1
  0010 = 2
  0011 = 3
  0100 = 4
  0101 = 5
  0110 = 6
  ...
  LSB - Least Significant Bit is present in odd numbers.

Is the algorithm counterintuitive?
Why is it not split across if (n & 1) { ... } else { ... }
  Odd number will shave off one `x` and double the x.
  The exponentiation always ends with n=1 and we join the last x*=x with r;

-------------------------------------------------------------------------------

The exponential number grows fast.
Modular arithmetic helps.
Using modulo of numbers helps keep numbers bounded.
We lose information of the original result of the number.
We work in the modular number system.
*/
class Solution {
 public:
  static constexpr int mod = 1e9 + 7;
  int monkeyMove(int n) {
    long long r = 1, x = 2;
    while (n > 0) {
      if (n & 1) r = (r * x) % mod;
      x = (x * x) % mod;
      n >>= 1;
    }
    return (r - 2 + mod) % mod;
  }
};

}  // namespace FastPow

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
