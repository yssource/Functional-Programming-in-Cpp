#include <future>

template<typename T, typename F>
// Takes a function from T to a future instance future<T2>
auto mbind(futuer<T> const& future, F f) {
  // Takes a function from future<T> and returns future<T2>. You need to pass a lambda to extract the value from the future object before passing it to f.
  return futuer.then(
    [](futuer<T> finished) {
      // Doesn't block anything because the continutaion is called only when the result is ready (or if an exception has occurred)
      return f(finished.get());
    });
}