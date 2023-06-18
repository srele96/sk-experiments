#include <bits/stdc++.h>
using namespace std;

size_t longest_substring(const string& m_string) {
  size_t m_max{0}, m_right = 0, m_left = 0, m_size = 0;
  char m_char;
  unordered_map<char, size_t> m_chars;

  while (m_right < m_string.length()) {
    m_char = m_string[m_right];
    m_chars[m_char] =
        m_chars.find(m_char) == m_chars.end() ? 1 : m_chars[m_char] + 1;

    ++m_size;
    ++m_right;

    if (m_chars.size() == m_size) {
      m_max = max(m_max, m_size);
    }

    while (m_chars.size() < m_size) {
      m_char = m_string[m_left];
      --m_chars[m_char];

      m_chars[m_char] == 0 && m_chars.erase(m_char);

      --m_size;
      ++m_left;
    }
  }
  return m_max;
}

int main() {
  assert(longest_substring("abcabcbb") == 3);
  assert(longest_substring("bbbbb") == 1);
  assert(longest_substring("pwwkew") == 3);
  assert(longest_substring("pw wke w") == 4);
  assert(longest_substring("123456789") == 9);
  assert(longest_substring("@a3 456789") == 10);

  return 0;
}
