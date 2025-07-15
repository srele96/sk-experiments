#include <vector>
using namespace std;

/*

O(n) time and O(1) space complexity solution explores the idea to use
mathematical formula to express how many times each number is contained within
the resulting sum

we proceed to multiply each value by that formula and append to the resulting
sum, i might have taken a month to figure that out by myself, i obviously
noticed plenty of repetition but i am far from inclined to use mathematical
formulas for algorithms

*/

/*

- it never occurred to me to inject stuff to binary search tree

- my only instinct was to iterate through input iteratively or recursively

- for two easy problems solvable using prefix sum i immediately knew how to use
  prefix sum
  - for hard problem i could not even smell a hint of where and how to use
    prefix sum
  - i decided to solve only easy problems by myself without looking at
  submissions

- i never needed to reiterate because by merging we can observe all those as one
number! it units them! prefix and postfix sums

- maybe i should combine unsolvable problems for at least 1 hour a day to expose
myself to strain in hopes to yield some skill (due to lack of guided practice -
deliberate practice)

- the problem was that i always expect to iterate over all input and such
thought hindered my problem solving

- easy problems require 1 trick, medium requires more tricks (but maybe even
easy ones require more than 1 but it feels like one due to my current skill)

- commonality between solutions

- i don't know plenty of low-level techniques (odd length sub-arrays)
  - i dont know how to get them - doing easy problems revealed my weakness

- some of these 'easy' problems will be very challenging and i SHOULD NOT HAVE
UNDERESTIMATED THEM

*/

/*

i had a big problem on how to iterate through all arrays of odd length, i had
spent like 20 minutes figuring it out

i conceptually knew how to roughly do it, i knew how to phrase that i want to
iterate through all odd sub-arrays, i had rough idea because i immediately
scribbled down that i wanna iterate for every odd length such as:
for(int i = 0; i < n; i += 2)
however i had no clue what should be within the loop and i had spent some time
scribbling down in the notebook how the values should change, what is their
changing pattern and how could i achieve such changing pattern in the code with
loops

*/

// https://leetcode.com/problems/sum-of-all-odd-length-subarrays/

namespace a {

class Solution {
 public:
  int sumOddLengthSubarrays(vector<int>& arr) {
    int n = arr.size();
    vector<int> prefix(n);
    prefix[0] = arr[0];
    // for the cost of additional O(n) space and memory
    // we reduce from O(n^3) to O(n^2)
    for (int i = 1; i < n; ++i) prefix[i] = prefix[i - 1] + arr[i];
    int sum = 0;
    // i was correct to assume that we would conceptually iterate first
    // over all desired lengths, and for each array of desired length within
    // for each odd length
    for (int i = 0; i < n; i += 2) {
      // for each start index of odd length
      for (int j = 0; j < n - i; ++j) {
        sum += prefix[j + i];
        if (j > 0) sum -= prefix[j - 1];
      }
    }
    return sum;
  }
};

}  // namespace a

namespace b {

class Solution {
 public:
  int sumOddLengthSubarrays(vector<int>& arr) {
    int n = arr.size();
    int sum = 0;
    // i was correct to assume that we would conceptually iterate first
    // over all desired lengths, and for each array of desired length within
    // for each odd length
    for (int i = 0; i < n; i += 2) {
      // for each start index of odd length
      for (int j = 0; j < n - i; ++j) {
        // for each index in the array of odd length
        for (int k = j; k <= j + i; ++k) {
          sum += arr[k];
        }
      }
    }
    return sum;
  }
};

}  // namespace b
