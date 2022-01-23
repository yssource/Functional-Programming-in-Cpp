#include "4.3-call-operator-for-partial-function-application.cpp"
#include <utility>

template <typename Function, typename SecondArgT>
partial_application_bind2nd_impl<Function, SecondArgT> bind2nd(Function&& function, SecondArgT&& second_arg) {
  return partial_application_bind2nd_impl<Function, SecondArgT>(
    std::forward<Function>(function), std::forward<SecondArgT>(second_arg));
}
