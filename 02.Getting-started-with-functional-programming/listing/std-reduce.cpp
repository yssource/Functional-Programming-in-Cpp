#include <vector>
#include <iostream>
#include <execution>

double average_score(std::vector<int> const& scores) {
  return std::reduce(
    std::execution::par,
    scores.cbegin(), scores.cend(),
    0
    ) / static_cast<double>(scores.length());    // std::vector<int>::length() ?
//    ) / static_cast<double>(scores.size());
}

int main() {
  std::vector<int> const sintel_scores{ 9, 7, 10, 5, 8, 8, 6 };

  std::cout << "Sintel(2010) average score: " << average_score(sintel_scores) << std::endl;
}
