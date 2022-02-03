#include <stdexcept>

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
};