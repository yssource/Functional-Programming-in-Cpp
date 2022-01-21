#include <vector>
#include <iostream>
#include <numeric>

double average_score(std::vector<int> const& scores) {
  // Sums all the scores in the collection
  return std::accumulate(
    scores.cbegin(), scores.cend(),
  // Initial value for summing
    0
  // Calculates the average score
  ) / static_cast<double>(scores.size());
}

int main() {
  std::vector<int> const sintel_scores{ 9, 7, 10, 5, 8, 8, 6 };

  std::cout << "Sintel(2010) average score: " << average_score(sintel_scores) << std::endl;
}
