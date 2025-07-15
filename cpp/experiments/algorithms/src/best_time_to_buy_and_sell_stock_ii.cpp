#include <bits/stdc++.h>
using namespace std;

/*
Interestingly, i haven't even thought about greedy approach here. Why? Don't
know. 18 months ago, 1.5 years ago, i solved the problem version I using greedy
approach. Did I get help from AI? No idea. I think back then I didn't get any AI
help.

Today i was thinking about how tf to approach the problem using dynamic
programming. I asked AI to give me a hint and it gave me the two recurrence
relations below. That immediately helped me understand how to solve the problem.
When trying to get dynamic programming problem done, i am looking for recurrence
relation which is essentially explaining the steps done at each step. At first i
was bamboozled on what steps to take. I thought ok... at each cell, a stock is
bought and sold... how do we know? we need a flag... ok... parameter... And then
if  we make a choice... we want to take a max out of the options we select...
ok... i didn't think about "what choice did i have yesterday" or "what choice
did i have previously"... if i did, i might have had the solution before i got
pissed the fuck off and asked AI for hint... ahhhhhh.... so annoyed....
never mind.

After seeing the relation, the whole problem revealed itself to me, making me
see that i had the problem solved and if i had kept going i would have had the
solution within the next 30 minutes or 1 hour or so... yeah.... i don't know...
today was not my day...

I just saw comment in the file that contains first part of the problem... how i
came up with the greedy algorithm... i said 18 months ago that i figured out
it's greedy... lol today didn't seem greedy at all! and after all, i am focusing
only on dynamic programming problems. I don't care much about other problem
types... i just want to ramp up on all dynamic programming problems that i
can... there are 600 dynamic programming problems on leetcode and i am going to
smack them all. My goal is to solve all dynamic programming problems... on
leetcode... and then... i don't know what... i don't know what do i do then... i
will just go and cry in a corner... or something... i got my place to be now...
these files... this repo... it has gone a long way... a long way... really...
you know...
*/

// Meh, quite garbage
// Thanks to a hint from gpt, it didn't take me more than 30 minutes to figure
// out the rest... jesus christ, that sucks, major spoiler, crap damn it ffs
//
// The hint:
// dp[i][true] = max(dp[i-1][true], dp[i-1][false] - p[i])
// dp[i][false] = max(dp[i-1][false], dp[i-1][true] + p[i])
//
// From there... The rest was easy as fuck...
// Another hint... 2 variables... easy as fuck... jesus
namespace bottomUp {

class Solution {
 public:
  int maxProfit(vector<int>& p) {
    int m = p.size() - 1;
    constexpr int sz = 3e4;
    array<unordered_map<bool, int>, sz> dp;
    dp[0][true] = -p[0];
    dp[1][false] = 0;
    for (int i = 1; i <= m; ++i) {
      dp[i][true] = max(dp[i - 1][true], dp[i - 1][false] - p[i]);
      dp[i][false] = max(dp[i - 1][false], dp[i - 1][true] + p[i]);
    }
    return max(dp[m][true], dp[m][false]);
  }
};

}  // namespace bottomUp

namespace twoVariables {

class Solution {
 public:
  int maxProfit(vector<int>& p) {
    int held_y = -p[0];
    int held_n = 0;
    for (int i = 1; i < p.size(); ++i) {
      held_y = max(held_y, held_n - p[i]);
      held_n = max(held_n, held_y + p[i]);
    }
    return max(held_y, held_n);
  }
};

}  // namespace twoVariables

namespace topDown {

class Solution {
 public:
  int maxProfit(vector<int>& p) {
    int m = p.size() - 1;
    vector<unordered_map<bool, int>> dp(m + 1);
    function<int(const int, const bool)> f = [&](const int i, const bool h) {
      if (dp[i].find(h) != dp[i].end()) return dp[i][h];
      if (i == 0) return dp[i][h] = h ? -p[i] : 0;
      return dp[i][h] = max(f(i - 1, h), f(i - 1, !h) + (h ? -1 : 1) * p[i]);
    };
    return max(f(m, true), f(m, false));
  }
};

}  // namespace topDown
