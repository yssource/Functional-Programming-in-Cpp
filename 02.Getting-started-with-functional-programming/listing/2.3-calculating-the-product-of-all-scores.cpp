#include <functional>
#include <numeric>
#include <vector>
double scores_product(std::vector<int> const& scores) {
  // Calculates the product of all the scores
  return std::accumulate(
    scores.cbegin(), scores.cend(),
  // Initial value for calculating the product
    1,
  // Multiplies the scores instead of summing
    std::multiplies<int>()
  );
}
