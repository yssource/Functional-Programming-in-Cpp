#include <type_traits>

template<typename T>
using contained_type_t =
  std::remove_cv_t<
    std::remove_reference_t<
      decltype(*begin(std::declval<T>()))
    >
  >;