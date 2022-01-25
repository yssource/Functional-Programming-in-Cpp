#include <vector>

// You can use a vector as the cache because in order to out fib(n), you need to
// know fib(k) for all k < n.
std::vector<unsigned> cache{ 0, 1 };

unsigned fib(unsigned n) {
  // Returns the value if it's already in the cache
  if (cache.size() > n) {
    return cache[n];
  }
  // Gets the result and adds it to the cache. You can use push_back to add the
  // nth element, because you know all the previous values are filled.
  auto const result{ fib(n - 1) + fib(n - 2) };
  cache.push_back(result);

  return result;
}
