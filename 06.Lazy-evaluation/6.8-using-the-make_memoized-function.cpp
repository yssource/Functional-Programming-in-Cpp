#include "6.7-creating-a-memoized-wrapper-from-a-function-pointer.cpp"
#include <iostream>

/*
class fib_cache {
  public:
  fib_cache()
    : size_{ 2 }
    , previous_{ 0 }
    , last_{ 1 } {}

  size_t size() const {
    return size_;
  }

  unsigned operator[](unsigned n) const {
    return n == size_ - 1 ? last_ :
           n == size_ - 2 ? previous_ :
                            0;
  }

  void push_back(int val) {
    ++size_;
    previous_ = last_;
    last_ = val;
  }

  private:
  unsigned size_;
  int previous_;
  int last_;
};

fib_cache cache;

int fib(unsigned n) {
  if (cache.size() > n) {
    return cache[n];
  } else {
    cache.push_back(fib(n - 1) + fib(n - 2));
    return cache[n];
  }
}
*/

int fib(unsigned n) {
  if (n < 2) {
    return n;
  }
  return fib(n - 1) + fib(n - 2);
}

int main() {
  auto fibmemo{ make_memoized(fib) };

  // Calculates fibmemo(15) and caches the result
  std::cout << "fib(15) = " << fibmemo(15) << std::endl;
  // The next time fibmemo(15) is called, loads the result from the cache
  // instead of calculating it again
  std::cout << "fib(15) = " << fibmemo(15) << std::endl;
}
