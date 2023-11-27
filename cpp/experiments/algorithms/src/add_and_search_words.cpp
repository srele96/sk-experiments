#include <bits/stdc++.h>
using namespace std;

// https://leetcode.com/problems/design-add-and-search-words-data-structure/submissions/

class WordDictionary {
 private:
  std::unordered_map<std::string, WordDictionary*> children;
  bool end{false};

 public:
  WordDictionary() {}

  void addWord(string word) {
    struct addWord {
      void operator()(const std::string& word, WordDictionary* node,
                      const std::size_t i = 0) {
        if (i < word.size()) {
          const std::string key{word[i]};
          if (node->children[key] == nullptr) {
            node->children[key] = new WordDictionary;
          }
          (*this)(word, node->children[key], i + 1);
        } else {
          node->end = true;
        }
      }
    };

    addWord{}(word, this);
  }

  bool search(string word) {
    struct search {
      bool operator()(const std::string& word, const WordDictionary* node,
                      const std::size_t i = 0) {
        if (i < word.size()) {
          const std::string key{word[i]};
          if (key != ".") {
            if (node->children.find(key) == node->children.end()) {
              return false;
            }
            return (*this)(word, node->children.at(key), i + 1);
          }
          // that did the trick... if we hit a dot, we don't know which subtree
          // matches the remainder of the string so the solution i figured out
          // was to perform the same search on each subtree and if any of them
          // matches, we return otherwise we found no matches i could not return
          // the function call because the first false would terminate the for
          // loop
          //
          // how did i come up with this solution? well the other day i was
          // thinking about how to solve the problem using a hashmap, i was
          // imagining the trie in my mind and what would i do if i encounter a
          // dot, i realized that without a trie, a dot would mean that any
          // letter could replace it and i would need to for one dot replace it
          // with each other letter in alphabet to check if it matches to any
          // string we currently store in the set, if we had two dots, that
          // would mean each combination of the two dots needs to be checked
          // against all the values in the set... and in fact i could implement
          // that algorithm right now
          //
          // the next idea was, what happens when there is a dot? i tried to
          // understand the problem better, and it yielded quite good results, i
          // solved a medium problem with little effort it felt, also tries are
          // just a way of thinking, a way of arranging data, i realize that the
          // way i arrange data allows me to efficiently or non efficiently
          // store the input which i can do various operations on after that...
          //
          // then i thought about, ok, once i encounter a dot, what do i do? how
          // do i know how each subtree matches against the remainder of the
          // string? i phrased it as such that i perform the same search but now
          // for each subtree instead of one character that matches, which means
          // that each recursion could branch out, actually that feels like
          // there are overlapping subproblems...
          //
          // and then i thought about ok, if i imagine that in each for loop
          // iteration i have a result of the whole subtree without thinking
          // much about it, do i need a separate search procedure or not, i
          // tried to write a separate procedure for that and realized that the
          // signature and the logic was the same as the logic inside the struct
          // and also realized that if i within that procedure also had to
          // handle another dot that would occur, resulting in me creating third
          // procedure, and that is when it hit me that the initial search
          // worked fine, if there is no dot, we find one child that matches the
          // current character and proceed, if there is a dot, we have to
          // perform the same search for all children and only terminate with
          // success if we find a success, at the very end we terminate with
          // false because that means we did not find any matching subtree after
          // iterating through every subtree...
          for (auto itr{node->children.begin()}; itr != node->children.end();
               ++itr) {
            if ((*this)(word, itr->second, i + 1)) {
              return true;
            }
          }
          return false;
        } else {
          return node->end;
        }
      }
    };

    return search{}(word, this);
  }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */
