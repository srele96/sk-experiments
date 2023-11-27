#include <bits/stdc++.h>

using namespace std;

using vi = vector<int>;

void sift_down(vi& numbers, int i) {
  int h = i;
  int l = 2 * i + 1;
  int r = 2 * i + 2;
  int len = numbers.size() - 1;

  if (l < len && numbers[l] > numbers[h]) h = l;
  if (r < len && numbers[r] > numbers[h]) h = r;
  if (h != i) {
    swap(numbers[i], numbers[h]);
    sift_down(numbers, h);
  }
}

void heapify(vi& numbers) {
  for (int i = numbers.size() / 2 - 1; i >= 0; --i) sift_down(numbers, i);
}

void p_numbers(vi& numbers) {
  for (int n : numbers) {
    cout << n << ' ';
  }
}

int main() {
  vi numbers{3, 1, -3, 4, 19, 3, -10};
  p_numbers(numbers);
  heapify(numbers);
  cout << '\n';
  p_numbers(numbers);

  return 0;
}
