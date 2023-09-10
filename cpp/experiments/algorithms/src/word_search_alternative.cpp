#include <bits/stdc++.h>
using namespace std;

// https://leetcode.com/problems/word-search-ii/submissions/

// Time Limit Exceeded.
//
// The solution creates a trie from the board. It uses backtracking technique to
// create a trie from the board and compares words to the ones in the board. If
// the search doesn't terminate, a word exists.

class Solution {
 public:
  vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
    struct trie {
      unordered_map<string, trie*> children;
      bool find(const string& word) {
        struct inner_find {
          bool operator()(const string& word, trie* node, int i = 0) {
            if (i < word.size()) {
              // cout << word << " " << word[i] << "\n";
              string key = string{word[i]};
              if (node->children.find(key) == node->children.end()) {
                return false;
              }
              return (*this)(word, node->children.at(key), i + 1);
            } else {
              return true;
            }
          }
        };
        return inner_find{}(word, this);
      }
    };

    struct create {
      vector<vector<char>>& board;
      vector<vector<bool>> visited;
      vector<pair<int, int>> directions;
      create(int n, int m, vector<vector<char>>& _board)
          : board{_board},
            visited{vector<vector<bool>>(n, vector<bool>(m, false))},
            directions{init_directions()} {}
      int left(int j = 0) const { return j - 1; }
      int right(int j = 0) const { return j + 1; }
      int up(int i = 0) const { return i - 1; }
      int down(int i = 0) const { return i + 1; }
      int stay() const { return 0; }
      vector<pair<int, int>> init_directions() const {
        return {{up(), stay()},
                {stay(), right()},
                {down(), stay()},
                {stay(), left()}};
      }
      bool can_visit(int i, int j) {
        return i >= 0 && i < board.size() && j >= 0 && j < board[0].size();
      }
      bool can_visit_node(int i, int j) {
        return can_visit(i, j) && !visited[i][j];
      }
      void operator()(int i, int j, trie* node) {
        visited[i][j] = true;
        string c = string{board[i][j]};
        if (node->children.find(c) == node->children.end()) {
          trie* child_node = new trie;
          node->children[c] = child_node;
        }
        // cout << i << " " << j <<  " " << c << "\n";

        for (auto& [i_direction, j_direction] : directions) {
          const int new_i = i + i_direction;
          const int new_j = j + j_direction;
          if (can_visit_node(new_i, new_j)) {
            (*this)(new_i, new_j, node->children[c]);
          }
        }

        visited[i][j] = false;
      }
    };

    create create_trie(board.size(), board[0].size(), board);
    trie* root = new trie;
    for (int i = 0; i < board.size(); ++i) {
      for (int j = 0; j < board[i].size(); ++j) {
        create_trie(i, j, root);
        // cout << "\n\n";
      }
    }

    // trie looks ok as i thought...
    // function<void(trie*, int)> dfs{[&](trie* node, int level) {
    //     if (node != nullptr) {
    //         for(auto& p : node->children) {
    //             cout << p.first << " , level = " << level << "\n";
    //             dfs(p.second, level + 1);
    //         }
    //     }
    // }};
    // dfs(root, 0);

    vector<string> result;
    for (auto& word : words) {
      if (root->find(word)) {
        result.push_back(word);
      }
    }

    return result;
  }
};
