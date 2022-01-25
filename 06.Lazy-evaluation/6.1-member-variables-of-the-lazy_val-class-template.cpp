#include <mutex>

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

};
