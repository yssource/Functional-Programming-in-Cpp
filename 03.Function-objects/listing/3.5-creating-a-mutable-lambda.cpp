#include <algorithm>
#include <string>
#include <vector>
#include <cctype>
#include <iostream>

int main() {
  int count = 0;
  std::vector<std::string> words{ "An", "ancient", "pond" };

  std::for_each(words.cbegin(), words.cend(),
    // You're capturing "count" by value; all changes to it are localized and
    // visible only from the lambda.
    [count](std::string const& word)
    // mutable comes after the argument list and tells the compiler that the
    // call operator on this lambda shouldn't be const.
    mutable {
    if (std::isupper(word[0])) {
      std::cout << word << " " << count << std::endl;
    }
  });
}
