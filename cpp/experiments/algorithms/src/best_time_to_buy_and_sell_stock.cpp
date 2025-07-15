#include <vector>
using namespace std;

// how did i know? i just guessed, but i knew it's greedy... so i hacked my way
// through the solution i thought how i wanna buy cheaper stocks if there's any,
// hence initially any stock will be cheaper => 10e5 if the profit i achieve by
// selling the current stock is higher than currently accumulated one, we can
// store it this solution is differently written than the previous one i have
// implemented, but uses the same logic obtain cheapest stocks and sell when
// profit is the heighest for each stock we absolutely ignore the previous and
// next stocks, we simply care to greedily obtain cheapest stocks and sell for
// the heighest profit

class Solution {
 public:
  int maxProfit(vector<int>& prices) {
    int profit = 0, stock = 10e5;
    for (int i = 0; i < prices.size(); ++i) {
      // 2. then i realized i have to first attemp to buy stock with the
      // existing cheapest stock, before i replace the current stock with the
      // new one hence 10e5 makes the first stock never sold initially
      if (prices[i] - stock > profit) {
        profit = prices[i] - stock;
      }
      // 1. i first setup the buying of the highest stock if i encounter highet
      // stock
      if (prices[i] < stock) {
        stock = prices[i];
      }
    }
    return profit;
  }
};
