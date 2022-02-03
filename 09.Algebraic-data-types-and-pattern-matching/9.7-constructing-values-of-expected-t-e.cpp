#include <stdexcept>
#include <utility>

template<typename T, typename E>
class expected {
private:
  union {
    T value_;
    E error_;
  };

  bool valid_;

public:
  T& get() {
    if (!valid_) {
      throw std::logic_error("Missing a value");
    }
    return value_;
  }

  E& error() {
    if (valid_) {
      throw std::logic_error("There is no error");
    }

    return error_;
  }

  template<typename... Args>
  static expected success(Args&&... params) {
    // Default constructor that creates an uninitialized union
    expected result;
    // Initializes the union tag. You'll have a valid value inside.
    result.valid_ = true;
    // Calls placement new to initialize the value of type T in the
    // memory location of value_
    new (&result.value_) T(std::forward<Args>(params)...);
    return result;
  }

  template<typename... Args>
  static expected error(Args&&... params) {
    // Creating the error instance is the same,
    // apart from calling the constructor for type E
    // instead of the constructor of T.
    expected result;
    result.valid_ = false;
    new (&result.value_) E(std::forward<Args>(params)...);
    return result;
  }
};