class Solution {
 public:
  void backtrack(vector<vector<int>>& result, vector<int>& comb, int n, int k,
                 int last) {
    if (comb.size() == k) {
      result.push_back(comb);
      return;
    }
    for (int i = 1; i <= n; ++i) {
      if (i > last) {
        comb.push_back(i);
        backtrack(result, comb, n, k, i);
        comb.pop_back();
      }
    }
  }

  vector<vector<int>> combine(int n, int k) {
    vector<vector<int>> result;
    vector<int> comb;
    backtrack(result, comb, n, k, 0);
    return result;
  }
};
