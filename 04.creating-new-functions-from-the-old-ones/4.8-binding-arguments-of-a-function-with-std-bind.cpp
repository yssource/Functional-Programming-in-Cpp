#include <functional>

using namespace std::placeholders;

int main() {
  auto is_greater_than_42{ std::bind(std::greater<double>(), _1, 42) };
  auto is_less_than_42{ std::bind(std::greater<double>(), 42, _1) };

  is_less_than_42(6);     // true
  is_greater_than_42(6);  // false
}
