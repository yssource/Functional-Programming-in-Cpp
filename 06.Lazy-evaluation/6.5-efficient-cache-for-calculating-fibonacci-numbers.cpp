class fib_cache {
public:
  fib_cache()
    // Start of the Fibonacci series: {0, 1}
    : previous_{ 0 }
    , last_{ 1 }
    // Size of the cache (not excluding the forgotten values)
    , size_{ 2 } {}

  auto size() const -> size_t {
    return size_;
  }

  auto operator[](unsigned n) const -> unsigned {
    return n == size_ - 1 ? last_ :
           n == size_ - 2 ? previous_ :
                            0;
  }

  auto push_back(unsigned value) -> void {
    // Adds a new value to the cache, and increases the size
    size_++;
    previous_ = last_;
    last_ = value;
  }

private:
  int previous_;
  int last_;
  size_t size_;
};
