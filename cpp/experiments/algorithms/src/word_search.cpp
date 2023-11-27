#include <bits/stdc++.h>
using namespace std;

class Solution {
 public:
  struct trie {
    unordered_map<char, trie*> children;
    bool is_end = false;

    void insert(const string& word) {
      function<void(int, trie*)> m_insert{[&](int i, trie* node) {
        if (i < word.size()) {
          if (node->children.find(word[i]) == node->children.end()) {
            node->children[word[i]] = new trie;
          }
          m_insert(i + 1, node->children[word[i]]);
        } else {
          node->is_end = true;
        }
      }};

      m_insert(0, this);
    }

    static void deallocate(trie* node) {
      if (node != nullptr) {
        for (auto& child : node->children) {
          deallocate(child.second);
        }
        delete node;
      }
    }
  };

  vector<string> search_words(vector<vector<char>>& grid,
                              vector<string>& words) {
    vector<vector<bool>> visited(grid.size(),
                                 vector<bool>(grid[0].size(), false));

    function<bool(int, int)> within_bounds{[&](int i, int j) {
      return i >= 0 && i < grid.size() && j >= 0 && j < grid[i].size();
    }};

    trie* root = new trie;
    for (string& word : words) {
      root->insert(word);
    }

    vector<pair<int, int>> directions{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    string current_word;

    unordered_set<string> unique_matching_words;
    function<void(int, int, trie*)> search{[&](int i, int j, trie* node) {
      // cout << "received " << i << " " << j << "\n";
      if (node->children.find(grid[i][j]) != node->children.end()) {
        visited[i][j] = true;
        char key = grid[i][j];
        current_word.push_back(key);

        for (auto& [i_dir, j_dir] : directions) {
          int new_i = i + i_dir;
          int new_j = j + j_dir;

          if (within_bounds(new_i, new_j) && !visited[new_i][new_j]) {
            // cout << new_i << " " << new_j << " entering...\n";
            search(new_i, new_j, node->children[key]);
          }
        }

        // as we backtrack, the algorithm is going to pick up everything again,
        // since we work with unique words, we can use set and move it to a
        // vector
        if (node->children[key]->is_end) {
          unique_matching_words.insert(current_word);
        }
        // cout << current_word << ", is end " << node->children[key]->is_end <<
        // "\n";

        visited[i][j] = false;
        current_word.pop_back();
      }
    }};

    for (int i = 0; i < grid.size(); ++i) {
      for (int j = 0; j < grid[i].size(); ++j) {
        // cout << "size " << grid.size() << " " << grid[i].size() << "\n";
        // cout << "passing " << i << " " << j << "\n";
        search(i, j, root);
      }
    }

    trie::deallocate(root);

    return vector<string>(make_move_iterator(unique_matching_words.begin()),
                          make_move_iterator(unique_matching_words.end()));
  }

  vector<string> findWords(vector<vector<char>>& board, vector<string>& words) {
    return search_words(board, words);
  }
};

int main() {
  // [["o","a","b","n"],["o","t","a","e"],["a","h","k","r"],["a","f","l","v"]]
  // ["oa","oaa"]
  vector<vector<char>> board{{'o', 'a', 'b', 'n'},
                             {'o', 't', 'a', 'e'},
                             {'a', 'h', 'k', 'r'},
                             {'a', 'f', 'l', 'v'}};
  vector<string> words{"oa", "oaa"};

  for (const string& word : Solution{}.findWords(board, words)) {
    cout << word << " ";
  }

  return 0;
}
