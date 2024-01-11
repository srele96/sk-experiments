#include <iostream>
#include <vector>

using namespace std;

void print(const vector<vector<int>>& matrix) {
  for (const vector<int> row : matrix) {
    for (const int col : row) {
      cout << col << ", ";
    }
    cout << "\n";
  }
}

int main() {
  vector<vector<int>> matrix{
      {1, -2, 3, 2},   //
      {-3, 2, 1, -2},  //
      {9, 3, 2, 5},    //
      {3, 2, 5, -3},   //
  };
  vector<vector<int>> prefix(matrix.size(), vector<int>(matrix[0].size()));
  prefix[0][0] = matrix[0][0];
  for (int i = 0; i < prefix.size(); ++i) {
    for (int j = 0; j < prefix[i].size(); ++j) {
      if (i == 0 && j == 0) {
        prefix[i][j] = matrix[i][j];
      } else if (i == 0) {
        prefix[i][j] = prefix[i][j - 1] + matrix[i][j];
      } else if (j == 0) {
        prefix[i][j] = prefix[i - 1][j] + matrix[i][j];
      } else {
        prefix[i][j] = prefix[i - 1][j] + prefix[i][j - 1] -
                       prefix[i - 1][j - 1] + matrix[i][j];
      }
    }
  }

  print(matrix);
  cout << "\n";
  print(prefix);

  return 0;
}
