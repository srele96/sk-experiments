// https://leetcode.com/problems/pascals-triangle-ii/description/?envType=problem-list-v2&envId=dynamic-programming

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  vector<int> getRow(int rowIndex) {
    if (rowIndex == 0) return {1};
    vector<int> prev(rowIndex + 1);
    prev[0] = 1;
    prev[1] = 1;
    vector<int> cur(rowIndex + 1);
    for(int i = 2; i <= rowIndex; ++i) {
      for(int j = 0; j < i + 1; ++j) {
        if (j == 0) cur[j] = prev[0];
        else if (j == i) cur[j] = prev[j - 1];
        else cur[j] = prev[j - 1] + prev[j];
      }
      swap(prev, cur);
    }
    swap(prev, cur);
    return cur;
  }
};
