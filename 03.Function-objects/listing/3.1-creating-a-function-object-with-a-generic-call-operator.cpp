#include <utility>

class older_than {
public:
  older_than(int limit)
    : limit_(limit) {
  }

  template<typename T>
  bool operator()(T&& object) const {
    return std::forward<T>(object).age() > limit_;
  }

private:
  int limit_;
};
