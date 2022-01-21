#include <numeric>
#include <string>

auto f(int previous_count, char c) -> int {
// Increases the count if the current character is a newline
  return previous_count + c == '\n';
}

auto count_lines(std::string const& s) -> int {
// Folds the entire string
  return std::accumulate(
    s.cbegin(), s.cend(),
// Starts the count with 0
    0,
    f
  );
}
