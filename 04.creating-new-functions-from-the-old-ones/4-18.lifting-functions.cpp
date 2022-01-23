#include <algorithm>
template<typename Function>
auto pointer_lift(Function f) {
  return [f](auto* item) {
    if (item != nullptr) {
      f(*item);
    }
  };
}

template <typename Function>
auto collection_lift(Function f) {
  return [f](auto& items) {
    std::for_each(items.cbegin(), items.cend(), f);
  };
}
