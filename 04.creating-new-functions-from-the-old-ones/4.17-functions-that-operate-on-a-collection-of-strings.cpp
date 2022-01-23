#include <algorithm>
#include <string>
#include <utility>
#include <vector>
#include <map>

auto to_upper(std::string& string) -> void;

// You can see a pointer to a string as a collection that contains either on
// element or nothing. If the pointer points to a string, that string will be
// transformed.
auto pointer_to_upper(std::string* str) -> void {
  if (str) to_upper(*str);
}

// A vector can contain as many strings as you want. This function converts then
// all to uppercase.
auto vector_to_upper(std::vector<std::string>& strs) -> void {
  std::for_each(strs.cbegin(), strs.cend(), to_upper);
}

// The map contains pairs of <const int, std::string>. You're leaving the
// integer values untouched while uppercase.
auto map_to_upper(std::map<int, std::string>& strs) -> void {
  std::for_each(strs.cbegin(), strs.cend(),
    [](std::pair<int, std::string> pair) { to_upper(pair.second); });
}
