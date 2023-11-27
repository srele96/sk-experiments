function combine(n, k) {
  const result = [];
  function backtrack(comb, last = 0) {
    if (comb.length === k) {
      result.push(comb.slice());
      return;
    }
    for (let i = 1; i <= n; ++i) {
      if (i > last) {
        comb.push(i);
        backtrack(comb, i);
        comb.pop();
      }
    }
  }
  backtrack([]);
  return result;
}
