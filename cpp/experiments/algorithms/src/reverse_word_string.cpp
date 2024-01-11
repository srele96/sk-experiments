#include <bits/stdc++.h>
using namespace std;

std::string reverseWords(std::string s) {
    // Reverse the entire string
    std::reverse(s.begin(), s.end());
    cout << "|" << s << "|\n";

    int n = s.length();
    int start = 0; // Start of a word
    int end = 0; // End of a word

    while (end < n) {
        // Skip leading spaces
        while (start < n && s[start] == ' ') {
            start++;
        }

        // Move end to the next space or end of string
        end = start;
        while (end < n && s[end] != ' ') {
            end++;
        }

        // Reverse the current word
        std::reverse(s.begin() + start, s.begin() + end);

        // Move to the next word
        start = end;
    }

    // Remove any extra spaces between words
    int i = 0;
    int j = 0;
    while (j < n) {
        while (j < n && s[j] == ' ') {
            j++; // Skip spaces
        }
        while (j < n && s[j] != ' ') {
            s[i++] = s[j++]; // Move non-space characters to the left
        }
        if (j < n) {
            s[i++] = ' '; // Add a single space between words
        }
    }

    s.erase(s.begin() + i, s.end()); // Remove any remaining characters

    return s;
}

int main() {
    std::string s = "  hello   world  how are you   ";
    std::string reversed = reverseWords(s);
    std::cout << "Reversed string: " << reversed << std::endl;

    return 0;
}
