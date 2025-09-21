#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  int eraseOverlapIntervals(vector<vector<int>>& intervals) {
    // for(const auto& p : intervals) {
    //   cout << "[" << p[0] << ", " << p[1] << "], ";
    // }
    // cout << "\n\n";
    sort(intervals.begin(), intervals.end(),
         [](const auto& a, const auto& b) { return a[1] < b[1]; });
    // for(const auto& p : intervals) {
    //   cout << "[" << p[0] << ", " << p[1] << "], ";
    // }
    // cout << "\n\n";
    int end = intervals[0][1];
    int removed = 0;
    for (int i = 1; i < intervals.size(); ++i) {
      if (intervals[i][0] < end) {
        ++removed;
        continue;
      }
      end = intervals[i][1];
    }
    return removed;
  }
};

/*

1 2
  2 3
1   3
    3 4

*/
