#include <bits/stdc++.h>

using namespace std;
using vi = vector<int>;

void counting_sort(vi& nums) {
  // No constraints, find largest
  int h = nums.at(0);
  for (int n : nums) h = max(n, h);
  // Create bookkeeping array
  vi bka;
  bka.resize(h + 1);
  // Count
  for (int n : nums) {
    ++bka.at(n);
  }
  // Insert values to original array
  int l = 0;
  for (size_t i = 0; i != bka.size(); ++i) {
    if (bka.at(i) > 0) {
      nums.at(l) = i;
      ++l;
    }
  }
}

void print_nums(vi& nums) {
  for (int n : nums) {
    cout << n << ' ';
  }
}

int main() {
  vi nums{10, 5, 4, 3, 2, 8, 9, 1, 10, 10};
  cout << "Before: ";
  print_nums(nums);
  cout << '\n';
  counting_sort(nums);
  cout << "After: ";
  print_nums(nums);

  return 0;
}
