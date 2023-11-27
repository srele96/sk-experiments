/**
 * @param {number[]} cost
 * @return {number}
 */
var minCostClimbingStairs = function (cost) {
  var dp = Array(cost.length);
  var mc = (i) => {
    if (dp[i]) return dp[i];
    if (i < cost.length) {
      dp[i] = Math.min(cost[i] + mc(i + 1), cost[i] + mc(i + 2));
      return dp[i];
    } else {
      return 0;
    }
  };
  return Math.min(mc(0), mc(1));
};
