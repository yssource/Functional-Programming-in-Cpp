#include <vector>
#include <iostream>

int main() {
  auto sum_max{
    1 + // Result of max({1})
    2 + // Result of max({1, 2})
    3   // Result of max({1, 2, 3})
  };

  std::cout << sum_max << std::endl;
}
