// Buy initial stock, so I have a value to calculate profit.
//
// The initial maximum profit is zero because I did not sell stock yet, and I
// use it for statistical purposes, so buying does not incur a loss, and I
// don't go in minus initially.
//
// Every day I calculate the profit if I sold owned stock today.
// If today's profit is the largest I ever had, save it.
//
// After calculating the profit for the currently owned stock, I check if
// today's one is cheaper and buy it if it is.
//
// Using that logic, I make sure to own a stock at the lowest price so I can
// sell it for the future highest.
//
// However, the cheapest stock on the last day means no more sell
// opportunities. Regardless, I still have the maximum profit I could ever
// achieve, so if, by accident, there is much more profit later and no cheaper
// stock, I will save it as the highest profit.

/**
 * @param {number[]} prices
 * @return {number}
 */
function max_profit(prices) {
  // Buy the initial stock.
  let bought_stock_price = prices[0];
  let max_profit_ever = 0;

  // Use variable for readability and as cache outside of the loop.
  let current_profit = undefined;

  for (let i = 1; i != prices.length; ++i) {
    // Calculate the profit for currently owned stock.
    current_profit = prices[i] - bought_stock_price;

    // Save today's profit if it's the largest ever.
    if (current_profit > max_profit_ever) {
      max_profit_ever = current_profit;
    }

    // Always buy the cheapest stock.
    if (prices[i] < bought_stock_price) {
      bought_stock_price = prices[i];
    }
  }

  return max_profit_ever;
}

module.exports.max_profit = max_profit;
