#include <algorithm>
#include <cctype>
#include <iostream>
#include <vector>
#include <string>
#include <range.h>

using namespace ranges::v3;

auto string_to_lower(std::string s) -> std::string {
  return s | view::transform(std::tolower);
}

auto string_only_alnum(std::string s) -> std::string {
  return s | view::filter(std::isalnum);
}

int main() {
  std::vector<std::string> words{ 
    istream_range<std::string>(std::cin)
    // Makes all words lowercase
    | view::transform(string_to_lower)
    // Keeps only letters and digits
    | view::transform(string_only_alnum)
    // You may get empty strings as the result when a token doesn't contain a
    // single letter or a digit, so you need to skip those.
    | view::remove_if(&std::string::empty)
  };
}
