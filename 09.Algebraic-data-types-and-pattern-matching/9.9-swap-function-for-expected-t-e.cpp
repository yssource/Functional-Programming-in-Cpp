#include <stdexcept>
#include <string>
#include <utility>
#include <optional>
#include <variant>

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

  void swap(expected& other) {
    using std::swap;
    if (valid_) {
      if (other.valid_) {
        // If "other" contains a value and so does the this
        // instance, swap them.
        swap(value_, other.value_);
      } else {
        // If the this instance is valid but "other" contains an error,
        // store the error in a temporary variable so you can move
        // your value into "other". Then you can safely set the error
        // for your instance.
        auto temp{ std::move(other.error_) };
        other.error.~E();
        new (&other.value_) T(std::move(value_));
        value_.~T();
        new (&error_) E(std::move(other.error()));
        swap(other.valid_, valid_);
      }
    } else {
      if (other.valid_) {
        // If "this" contains an error and "other" is valid,
        // you can base the implementation on the previous case.
        other.swap(*this);
      } else {
        // If both instances contain an error, swap the error values.
        swap(error_, other.error_);
      }
    }
  }

  // The assignment operator is trivial. The "other" argument contains
  // a copy of the value you want assigned to your instance. (You get
  // "other" by value, not as a const reference.) You swap it with
  // your instance.
  expected& operator=(expected other) {
    swap(other);
    return *this;
  }

  operator bool() const {
    return valid_;
  }

  operator std::optional<T>() const {
    if (valid_) {
      return value_;
    } else {
      return std::optional<T>();
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

template<typename T, typename Variant,
  typename Expected = expected<T, std::string>>
Expected get_if(Variant const& variant) {
  T* ptr{ std::get_if<T>(variant) };

  if (ptr != nullptr) {
    return Expected::success(*ptr);
  } else {
    return Expected::error("Variant doesn't contain the desired type");
  }
}