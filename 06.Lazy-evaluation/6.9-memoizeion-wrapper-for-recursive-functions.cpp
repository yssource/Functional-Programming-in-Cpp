#include "6.7-creating-a-memoized-wrapper-from-a-function-pointer.cpp"
#include <iostream>
#include <map>
#include <mutex>
#include <tuple>
#include <type_traits>

// Dummy class used in the contructor to avoid overload collision with
// copy-constructor
class null_param {};

template<typename Sig, typename F>
class memoize_helper;

template<typename Result, typename... Args, typename F>
class memoize_helper<Result(Args...), F> {
private:
  using function_type = F;
  using args_tuple_type = std::tuple<std::decay_t<Args>...>;

  function_type f;
  // Defines the cache, and, because it's mutable, synchronizes all the changes
  mutable std::map<args_tuple_type, Result> cache_;
  mutable std::recursive_mutex cache_mutex_;

public:
  template<typename Function>
  // The contructors need to initialize the wrapped function. You could made
  // copy-constructor copy the cached values as well, but that's not necessary.
  memoize_helper(Function&& f, null_param) : f(f) {}
  memoize_helper(memoize_helper const& other) : f(other.f) {}

  template<typename... InnerArgs>
  Result operator()(InnerArgs&&... args) const {
    std::unique_lock<std::recursive_mutex> lock{ cache_mutex_ };

    // Searches for the cached value
    auto const args_tuple{ std::make_tuple(args...) };
    auto const cached{ cache_.find(args_tuple) };

    if (cached != cache_.end()) {
      // If the cached value is found, returns it without calling f
      return cached->second;
    } else {
      // If the cached value isn't found, calls f and stores the result. Passes
      // *this as the first argument: the function to be used for the recursive
      // call.
      auto&& result{ f(*this, std::forward<InnerArgs>(args)...) };
      cache_[args_tuple] = result;
      return result;
    }
  }
};

template <typename Sig, typename F>
auto make_memoized_r(F&& f)
  -> memoize_helper<Sig, std::decay_t<F>> {
  return { std::forward<F>(f), null_param() };
}

int main() {
  auto fibmemo{ make_memoized_r<unsigned(unsigned)>(
    [](auto& fib, unsigned n) {
      std::cout << "Calculating " << n << "!\n";
      return n == 0 ? 0
           : n == 1 ? 1
           : fib(n - 1) + fib(n - 2);
    })};

  // Calculates fibmemo(15) and caches the result
  std::cout << "fib(15) = " << fibmemo(15) << std::endl;
  // The next time fibmemo(15) is called, loads the result from the cache
  // instead of calculating it again
  std::cout << "fib(15) = " << fibmemo(15) << std::endl;
}
