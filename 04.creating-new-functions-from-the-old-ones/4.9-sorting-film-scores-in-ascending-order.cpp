#include <algorithm>
#include <functional>
#include <vector>
using namespace std::placeholders;

int main() {
  std::vector<double> scores{ 1.9, 59.99, 60.01, 119.9, 95.8 };

  std::sort(scores.begin(), scores.end(),
    std::bind(std::greater<double>(), _2, _1));
}
