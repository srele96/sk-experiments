#include <bits/stdc++.h>
using namespace std;

namespace a {

class Solution {
 public:
  /**
   * Whether it's a leading zero or somewhere within the encoded string it's a
   * problem so we have to guard against it.
   */
  bool canDecodeOne(const string& encoded) { return encoded != "0"; }

  /**
   * When the algorithm attempts to decode '34' as two, it will fail. This guard
   * is necessary against invalid combinations of two encoded digits.
   */
  bool canDecodeTwo(const string& encoded) {
    return encoded[0] == '1' || (encoded[0] == '2' && encoded[1] != '7' &&
                                 encoded[1] != '8' && encoded[1] != '9');
  }

  /**
   * The algorithm produces all valid decoded strings.
   *
   * The recursion states:
   *
   * If we have only one character, decode it.
   * If we have two characters, decode it:
   *  - Combine each decoded one character.
   *  - Decode as two
   * For each n-1th decoded string:
   *  - Decode from start until the last digit
   *  - Take the last digit and decode it
   *  - Merge decoded start and last digit
   * For each n-2th decoded string:
   *  - Decode from start until the last two digits
   *  - Take the last two digits and decode them
   *  - Merge decoded start and last two digits
   */
  vector<string> decodeAll(const string& encoded,
                           const unordered_map<string, string>& decode) {
    if (encoded.size() == 1) {
      vector<string> decodedStrings;
      if (canDecodeOne(encoded)) {
        decodedStrings.push_back(decode.at(encoded));
      }
      return decodedStrings;
    }
    if (encoded.size() == 2) {
      vector<string> decodedStrings;
      if (canDecodeOne(encoded.substr(0, 1)) &&
          canDecodeOne(encoded.substr(1, 2))) {
        decodedStrings.push_back(decode.at(encoded.substr(0, 1)) +
                                 decode.at(encoded.substr(1, 2)));
      }
      if (canDecodeTwo(encoded)) {
        decodedStrings.push_back(decode.at(encoded));
      }
      return decodedStrings;
    }
    vector<string> decodedStrings;
    for (string decodedStart :
         decodeAll(encoded.substr(0, encoded.size() - 1), decode)) {
      if (canDecodeOne(encoded.substr(encoded.size() - 1))) {
        decodedStrings.push_back(decodedStart +
                                 decode.at(encoded.substr(encoded.size() - 1)));
      }
    }
    for (string decodedStart :
         decodeAll(encoded.substr(0, encoded.size() - 2), decode)) {
      if (canDecodeTwo(encoded.substr(encoded.size() - 2))) {
        decodedStrings.push_back(decodedStart +
                                 decode.at(encoded.substr(encoded.size() - 2)));
      }
    }
    return decodedStrings;
  }

  int numDecodings(string s) {
    /**
     * Build the map for digit decodings.
     */
    unordered_map<string, string> decode{[] {
      unordered_map<string, string> decode;
      int n = 1;
      for (char i = 'A'; i != '['; ++i) {  // '[' is after 'Z'
        decode[to_string(n)] = string(1, i);
        ++n;
      }
      return decode;
    }()};

    return decodeAll(s, decode).size();
  }
};

}  // namespace a

int main() {
  unordered_map<string, string> decode{[] {
    unordered_map<string, string> decode;
    int n = 1;
    for (char i = 'A'; i != '['; ++i) {  // '[' is after 'Z'
      decode[to_string(n)] = string(1, i);
      ++n;
    }
    return decode;
  }()};

  int t;
  cin >> t;
  while (t-- > 0) {
    string encoded;
    cin >> encoded;

    for (const string& decoded : a::Solution{}.decodeAll(encoded, decode)) {
      cout << decoded << ", ";
    }
    cout << "\n";
  }

  return 0;
}
