#include <bits/stdc++.h>

// https://leetcode.com/problems/implement-trie-prefix-tree/submissions/

namespace LeetCode {

using namespace std;

class Trie {
  std::unordered_map<std::string, Trie*> children;
  bool end{false};

 public:
  Trie() {}

  void insert(string word) {
    struct insert {
      void operator()(const std::string& word, Trie* node,
                      const std::size_t i = 0) {
        if (i < word.size()) {
          const std::string key{word[i]};
          // Don't override the end flag.
          if (node->children[key] == nullptr) {
            node->children[key] = new Trie;
          }
          (*this)(word, node->children[key], i + 1);
        } else {
          node->end = true;
        }
      }
    };

    insert{}(word, this);
  }

  bool search(string word) {
    struct search {
      bool operator()(const std::string& word, const Trie* node,
                      const std::size_t i = 0) {
        if (i < word.size()) {
          const std::string key{word[i]};
          if (node->children.find(key) == node->children.end()) {
            return false;
          }
          return (*this)(word, node->children.at(key), i + 1);
        } else {
          return node->end;
        }
      }
    };

    return search{}(word, this);
  }

  bool startsWith(string prefix) {
    struct starts_with {
      bool operator()(const std::string& prefix, const Trie* node,
                      const std::size_t i = 0) {
        if (i < prefix.size()) {
          const std::string key{prefix[i]};
          if (node->children.find(key) == node->children.end()) {
            return false;
          }
          return (*this)(prefix, node->children.at(key), i + 1);
        } else {
          return true;
        }
      }
    };

    return starts_with{}(prefix, this);
  }
};

}  // namespace LeetCode

namespace data_structure {

class trie {
 private:
  std::unordered_map<std::string, trie*> children;
  bool end{false};

 public:
  static trie* allocate();
  static void deallocate(trie* node);

  bool search(const std::string& string);
  bool starts_with(const std::string& string);
  void insert(const std::string& string);
};

}  // namespace data_structure

int main() {
  data_structure::trie* trie{data_structure::trie::allocate()};

  trie->insert("app");
  trie->insert("apple");
  std::cout << trie->search("apple") << "\n";
  std::cout << trie->search("app") << "\n";
  std::cout << trie->starts_with("app") << "\n";
  std::cout << trie->search("app");

  data_structure::trie::deallocate(trie);

  return 0;
}

bool data_structure::trie::search(const std::string& string) {
  struct search {
    bool operator()(const std::string& string, const trie* node,
                    const std::size_t i = 0) {
      if (i < string.size()) {
        const std::string key{string[i]};
        if (node->children.find(key) == node->children.end()) {
          return false;
        }
        return (*this)(string, node->children.at(key), i + 1);
      } else {
        return node->end;
      }
    }
  };

  return search{}(string, this);
}

bool data_structure::trie::starts_with(const std::string& string) {
  struct starts_with {
    bool operator()(const std::string& string, const trie* node,
                    const std::size_t i = 0) {
      if (i < string.size()) {
        const std::string key{string[i]};
        if (node->children.find(key) == node->children.end()) {
          return false;
        }
        return (*this)(string, node->children.at(key), i + 1);
      } else {
        return true;
      }
    }
  };

  return starts_with{}(string, this);
}

void data_structure::trie::insert(const std::string& string) {
  struct insert {
    void operator()(const std::string& string, trie* node,
                    const std::size_t i = 0) {
      if (i < string.size()) {
        const std::string key{string[i]};
        // Don't override the end flag.
        if (node->children[key] == nullptr) {
          node->children[key] = new trie;
        }
        (*this)(string, node->children[key], i + 1);
      } else {
        node->end = true;
      }
    }
  };

  insert{}(string, this);
}

data_structure::trie* data_structure::trie::allocate() { return new trie; }

void data_structure::trie::deallocate(data_structure::trie* node) {
  if (node != nullptr) {
    for (auto itr{node->children.begin()}; itr != node->children.end(); ++itr) {
      deallocate(itr->second);
    }
    delete node;
  }
}
