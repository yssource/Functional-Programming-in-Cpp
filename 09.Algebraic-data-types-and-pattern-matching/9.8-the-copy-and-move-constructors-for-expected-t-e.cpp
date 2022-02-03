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
  ~expected() {
    if (valid_) {
      value_.~T();
    } else {
      error_.~E();
    }
  }

  // The copy constructor initializes the flag that denotes whether
  // you have a value or an error.
  expected(expected const& other)
    : valid_(other.valid_) {
    if (valid_) {
      // If the instance being copied from contains a value,
      // you call the copy constructor on that value to
      // initialize the other value_ member variable using
      // the placement new syntax.
      new (&value_) T(other.value_);
    } else {
      new (&error_) E(other.error_);
    }
  }

  // The move constructor behaves like the copy constructor,
  // but you can steal the data from the original instance.
  expected(expected&& other)
    : valid_(other.valid_) {
      if (valid_) {
        // Instead of calling the copy constructor for value_
        // or error_, you can call the move constructor.
        new (&value_) T(std::move(other.value_));
      } else {
        new (&error_) E(std::move(other.error_));
      }
    }

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