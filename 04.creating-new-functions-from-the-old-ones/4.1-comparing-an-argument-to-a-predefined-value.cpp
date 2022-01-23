#include <algorithm>
#include <iostream>
#include <vector>

class greater_than {
  public:
  greater_than(int value)
    : value_(value) {}
  
  auto operator()(int arg) const -> bool {
    return arg > value_;
  }


  private:
  int value_;
};

auto main() -> int {
  std::vector<int> xs;

  greater_than greater_than_42(42);

  std::cout << greater_than_42(1) << ' ' << greater_than_42(50) << '\n';

  std::partition(xs.begin(), xs.end(), greater_than_42);
}
