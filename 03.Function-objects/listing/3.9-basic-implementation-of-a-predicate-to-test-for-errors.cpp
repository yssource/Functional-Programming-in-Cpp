#include <utility>
class error_test_t {
public:
  error_test_t(bool error = true)
    : error_(error) {}

  template<typename T>
  bool operator()(T&& value) const {
    // This usage of std::forward may seem strange, but it's nothing more than
    // perfectly forwarding the argument passed to the call operator as the
    // forwarding reference. You do the perfect forwarding becase error() could
    // be implemented differently for lvalue and rvalue references.
    return error_ == static_cast<bool>(std::forward<T>(value).error());
  }

  error_test_t operator==(bool test) const {
    // If the test is true, you're returning the same predicate you currently
    // have. If it's false, you're returning its negation.
    return error_test_t(test ? error_ : !error_);
  }

  error_test_t operator!() const {
    // You're returning the negation of the current predicate.
    return error_test_t(!error_);
  }

private:
  bool error_;
};

error_test_t error(true);
error_test_t not_error(false);
