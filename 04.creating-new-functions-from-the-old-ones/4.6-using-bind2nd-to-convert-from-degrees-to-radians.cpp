#include "4.4-wrapper-function-for-creating-the-previous-function-object.cpp"
#include <algorithm>
#include <functional>
#include <vector>

constexpr double PI{ 3.14 };

int main() {
  std::vector<double> degrees{ 0, 30, 45, 60 };
  std::vector<double> radians(degrees.size());

  // Iterates through all elements in the degrees vector
  std::transform(degrees.cbegin(), degrees.cend(),
    // Saves the converted results to the radians vector
    radians.begin(),
    // Passes multiplication with the second argument bound to π/180 as the
    // transformation function
    bind2nd(std::multiplies<double>(), PI / 180));
}
