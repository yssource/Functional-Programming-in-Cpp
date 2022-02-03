template<typename T, typename E>
class expected {
private:
  union {
    T value_;
    E error_;
  };

  bool valid_;
};