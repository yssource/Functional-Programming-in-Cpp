#include <mutex>
#include <utility>

template<typename F>
class lazy_val {
private:
  // Stores the function object that defines the computation
  F computation_;
  // You need to be able to tell whether you're already cached the computation
  // result.
  mutable bool cache_initialized_;
  // Cache for the computed result. The type of the member variable is the
  // return you of the computation.
  mutable decltype(computation_()) cache_;
  // You need the mutex in order to stop multiple threads from trying to
  // initialize the cache at the same time.
  mutable std::mutex cache_mutex_;

public:
  lazy_val(F computation)
  // Initializes the computation definition.
  // Note the cache isn't initialized yet.
    : computation_(computation)
    , cache_initialized_(false) {}
};

// Convenience function that creates a new lazy_val instance automatically
// deducing the type of the computation
template<typename F>
inline lazy_val<F> make_lazy_val(F&& computation) {
  return lazy_val<F>(std::forward<F>(computation));
}
