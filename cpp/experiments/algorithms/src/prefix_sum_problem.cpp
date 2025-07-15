#include <iostream>
#include <vector>

using namespace std;

/*

Prefix Sum Problem:

Problem Statement: You are given an array of integers and a set of queries.
Each query is represented by two integers L and R. For each query, you need to
find the sum of elements in the array from index L to R, inclusive. Assume array
indices start from 0.

Example:

  - Input Array: [1, 2, 3, 4, 5]

  - Queries: [(0, 2), (1, 3), (2, 4)]

  - Expected Output: [6, 9, 12] (The sums of elements from indices 0 to 2,
    1 to 3, and 2 to 4, respectively.)

*/

void something() {
  vector<int> numbers{5, 4, 6, 7, 8, 9};
  const size_t size = numbers.size();
  vector<int> prefix(size);
  vector<int> postfix(size);

  prefix[0] = numbers[0];
  const size_t last = size - 1;
  postfix[last] = numbers[last];
  for (int i = 1; i < size; ++i) {
    prefix[i] = numbers[i] + prefix[i - 1];
  }
  for (int i = last - 1; i >= 0; --i) {
    postfix[i] = numbers[i] + postfix[i + 1];
  }

  for (const int i : numbers) cout << i << ", ";
  cout << "\n";
  for (const int i : prefix) cout << i << ", ";
  cout << "\n";
  for (const int i : postfix) cout << i << ", ";
  cout << "\n";
  for (int i = 0; i < size; ++i) {
    cout << numbers[i] + prefix[i] + postfix[i] << ", ";
  }
  cout << "\n";
}

void solve() {
  int n, q;
  cin >> n >> q;
  vector<int> numbers(n);
  vector<pair<int, int>> query(q);
  for (int& i : numbers) cin >> i;
  for (pair<int, int>& q : query) {
    cin >> q.first >> q.second;
    --q.first;
    --q.second;
  }
  // -------
  // debug
  // for (int i : numbers) cout << i << ", ";
  // cout << "\n";
  // for (pair<int, int> q : query) cout << q.first << ", " << q.second << "\n";
  // -------
  vector<int> prefix(numbers.size());
  prefix[0] = numbers[0];
  for (int i = 1; i < numbers.size(); ++i) {
    prefix[i] = numbers[i] + prefix[i - 1];
  }
  for (const auto& q : query) {
    // i didn't realize that instead of calculating prefix sums from [0, n] to
    // [n, n] i could use mathematical formula because

    /*

    1, 2, 3, 4, 5
    how do we calculate sum [3, 5]
    we subtract [3, 5] - [1, 2]
    the difference of sums is the prefix sum

    */

    /*
    the issue was that i thought of a subtraction in a blink of a second and
    discarded that solution because i didn't immediately see how it would
    benefit me in efficiently calculating the sum

    another problem is that decision happened in a blink of an eye and i
    couldn't even reconsider or recall it consciously, even if i did, i probably
    would have skipped it because i didn't immediately realize that would lead
    to an optimal solution

    however solving the problem in brute force O(n^2) has helped me to get a
    better understanding of a problem which boosted my confidence and led me to
    solve the problem optimally using O(2n) solution and O(n) memory

    in this case we sacrificed O(n) memory to precompute prefixes and through
    mathematical calculation
    */
    if (q.first > 0) {
      cout << prefix[q.second] - prefix[q.first - 1];
    } else {
      cout << prefix[q.second];
    }
    cout << " ";

    // ---------
    // debug
    // ---------
    // optimized away O(n) iterations below
    // ---------
    // int sum = 0;
    // for (int i = q.first; i <= q.second; ++i) {
    //   sum += numbers[i];
    // }
    // cout << sum << " ";
    // ---------
  }
}

int main() {
  int t;
  cin >> t;
  while (t-- > 0) {
    solve();
  }
  return 0;
}
