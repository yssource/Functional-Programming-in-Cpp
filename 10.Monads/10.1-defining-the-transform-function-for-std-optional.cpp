#include <optional>

template<typename T1, typename F>
auto transform(std::optional<T1>& opt, F f)
  // Specify the return type, because you're returning just {}
  // when there's no value.
  -> decltype(std::make_optional(f(opt.value()))) {
  if (opt) {
    // If opt contains a value, transforms it using f and returns
    // the transformed value in a new instance of std::optional
    return std::make_optional(f(opt.value()));
  } else {
    // If no value, returns an empty instance of std::optional
    return {};
  }
}