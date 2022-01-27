#include <algorithm>
#include <cctype>
#include <functional>
#include <iostream>
#include <iterator>
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
  
  auto const results{ words
    // Groups multiple occurrences of words from the words range
    | view::group_by(std::equal_to<>())
    | view::transform([](auto const& group) {
      // Gets the size of each group, and returns a pair consisting of the word
      // frequency and the word
      auto const begin{ std::begin   (group)      };
      auto const end  { std::end     (group)      };
      auto const count{ std::distance(begin, end) };
      auto const word {              *begin       };

      return std::make_pair(count, word);
    })
    // To sort the words by frequency, you first need to convert the range into
    // a vector.
    | to_vector
    | action::sort
  };

  for (auto value : results
    | view::reverse
    | view::take(n)) {
    std::cout << value.first << ' ' << value.second << std::endl;
  }
}
