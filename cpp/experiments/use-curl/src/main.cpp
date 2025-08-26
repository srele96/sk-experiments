#include <curl/curl.h>

#include <iostream>
#include <string>

int main() {
  CURL *curl = curl_easy_init();
  const std::string documentation = "https://everything.curl.dev/libcurl/examples/get";

  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, documentation.c_str());
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
      std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << "\n";
    }

    curl_easy_cleanup(curl);
  }

  return 0;
}
