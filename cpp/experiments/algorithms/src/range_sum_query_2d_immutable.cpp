#include <iostream>
#include <vector>

using namespace std;

/*

a thing that might work is to study a topic, such as prefix and postfix sums and
then look for problems that use such technique, solve them, analyze what worked
and didn't

the thing one is supposed to notice that area of a square is represented as
prefix sum, where we can use it to avoid recomputing values

a few things that we can notice, overlapping subproblems, for any cube smaller
than top_left = [0,0], bottom_right=[n,m], we recompute an area within the
largest cube mentioned

what if there was a way to represent a size of every cube and a way to compute
the smaller cube in constant time O(1) from those values?

it somehow was just intuitive how to use the prefix table to solve this problem,
however if i was to solve this problem before, i wouldn't understand how to
solve it, i could be able to come up with brute force solution, i would go to
editorial, i would not understand editorial, i would proceed to understand the
code in the editorial, it was faster to read about prefix matrix, understand how
to compute prefix matrix, find a problem solvable using prefix matrix, solve the
problem using prefix matrix, now i can read editorials to explore alternate
solutions

i didn't notice that there was overlapping of the two specified areas which led
to me spending like 20 more minutes to figure out why the result area is
incorrectly computed, even though the prefix table contained correct values

the beauty of this problem is that in O(N * M) time we could construct the
prefix table which held information about area of any square within it, the
prefix table was rich with data that our algorithm could use to solve the
algorithmic computational problem

*/

// https://leetcode.com/problems/range-sum-query-2d-immutable/

namespace PrefixSum {

class NumMatrix {
 private:
  vector<vector<int>> m_prefix;

 public:
  NumMatrix(vector<vector<int>>& matrix)
      : m_prefix{
            vector<vector<int>>(matrix.size(), vector<int>(matrix[0].size()))} {
    m_prefix[0][0] = matrix[0][0];
    for (int i = 1; i < m_prefix.size(); ++i) {
      m_prefix[i][0] = m_prefix[i - 1][0] + matrix[i][0];
    }
    for (int j = 1; j < m_prefix[0].size(); ++j) {
      m_prefix[0][j] = m_prefix[0][j - 1] + matrix[0][j];
    }
    for (int i = 1; i < m_prefix.size(); ++i) {
      for (int j = 1; j < m_prefix[i].size(); ++j) {
        m_prefix[i][j] = m_prefix[i][j - 1] + m_prefix[i - 1][j] -
                         m_prefix[i - 1][j - 1] + matrix[i][j];
      }
    }
    // for(const auto& row : matrix) {
    //     for(const auto col : row) {
    //         cout << col << " ";
    //     }
    //     cout << "\n";
    // }
    // cout << "\n";
    // for(const auto& row : m_prefix) {
    //     for(const auto col : row) {
    //         cout << col << " ";
    //     }
    //     cout << "\n";
    // }
    // cout << "\n";
  }

  int sumRegion(int row1, int col1, int row2, int col2) {
    // if top is 0, no subtraction from top
    // if left is 0, no subtraction from left
    int sum = m_prefix[row2][col2];
    // cout << row1 << ", " << col1 << " & " << row2 << ", " << col2 << "\n";
    if (row1 > 0) {
      // cout << row1 - 1 << ", " << col2 << "\n";
      sum -= m_prefix[row1 - 1][col2];
    }
    if (col1 > 0) {
      // cout << row2 << ", " << col1 - 1 << "\n";
      sum -= m_prefix[row2][col1 - 1];
      if (row1 > 0) {
        sum += m_prefix[row1 - 1][col1 - 1];
      }
    }
    // cout << "\n\n";
    return sum;
  }
};

}  // namespace PrefixSum

namespace BruteForce {

class NumMatrix {
 private:
  vector<vector<int>> m_matrix;

 public:
  NumMatrix(vector<vector<int>>& matrix) : m_matrix{matrix} {}

  int sumRegion(int row1, int col1, int row2, int col2) {
    int sum = 0;
    for (int i = row1; i <= row2; ++i) {
      for (int j = col1; j <= col2; ++j) {
        sum += m_matrix[i][j];
      }
    }
    return sum;
  }
};

}  // namespace BruteForce
