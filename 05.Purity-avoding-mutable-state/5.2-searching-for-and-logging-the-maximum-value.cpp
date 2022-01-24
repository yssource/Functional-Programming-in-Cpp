#include <vector>
#include <cassert>
#include <algorithm>
#include <iostream>

auto max(std::vector<double> const& numbers) -> double {
  // Assume the numbers vector isn't empty, to have the std::max_element return
  // a valid iterator.
  assert(!numbers.empty());
  auto result{ std::max_element(numbers.cbegin(), numbers.cend()) };
  std::cerr << "Maximum is: " << *result << std::endl;
  return *result;
}

int main() {
  auto sum_max{
    max({1}) +
    max({1, 2}) +
    max({1, 2, 3})
  };

  std::cout << sum_max << std::endl;
}
