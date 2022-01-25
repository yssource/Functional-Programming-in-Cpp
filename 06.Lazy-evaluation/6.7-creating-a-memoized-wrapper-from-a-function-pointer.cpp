#include <map>
#include <tuple>

template<typename Result, typename... Args>
auto make_memoized(Result (*f)(Args...)) {
  // Creates a cache that maps tuples of arguments to the calculated results. If
  // you wanted to use this in a multithreaded environment, you'd need to
  // synchronize the changes to it with a mutex, as in listing 6.1.
  std::map<std::tuple<Args...>, Result> cache;

  return [f, cache](Args... args) mutable -> Result {
    auto const args_tuple{ std::make_tuple(args...) };
    auto const cached{ cache.find(args_tuple) };

    if (cached == cache.end()) {
      // In case of a cache miss, calls the function and stores the result to
      // the cache
      auto result{ f(args...) };
      cache[args_tuple] = result;
      return result;
    } else {
      // If the result is found in the cache, returns it to the caller
      return cached->second;
    }
  };
}
