#include <vector>
#include <iostream>

double average_score(std::vector<int> const& scores) {
  // Initial value for summing
  int sum = 0;

  // Sums the scores
  for (int score : scores) {
    sum += score; 
  }

  // Calculates the average score
  return sum / static_cast<double>(scores.size());
}

int main() {
  std::vector<int> const sintel_scores{ 9, 7, 10, 5, 8, 8, 6 };

  std::cout << "Sintel(2010) average score: " << average_score(sintel_scores) << std::endl;
}
