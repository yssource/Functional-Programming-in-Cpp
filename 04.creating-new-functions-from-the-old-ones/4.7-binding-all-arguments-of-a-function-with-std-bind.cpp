#include <functional>
int main() {
  // The std::greater function isn't yet invoked; you've created a function
  // object that will call std::greater with the specified values 6 and 42.
  auto bound{ std::bind(std::greater<double>(), 6, 42) };

  // Only when calling the bound function object are the elements 6 and 42
  // compared.
  bool is_6_greater_than_42{ bound() };
}
