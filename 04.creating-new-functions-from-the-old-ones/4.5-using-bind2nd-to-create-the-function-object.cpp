#include "4.4-wrapper-function-for-creating-the-previous-function-object.cpp"
#include <algorithm>
#include <functional>
#include <iostream>
#include <vector>

int main() {
  std::vector<int> xs;

  auto greater_than_42{ bind2nd(std::greater<int>(), 42) };

  std::cout << greater_than_42(1) << ' ' << greater_than_42(50) << '\n';

  std::partition(xs.begin(), xs.end(), bind2nd(std::greater<int>(), 6));
}
