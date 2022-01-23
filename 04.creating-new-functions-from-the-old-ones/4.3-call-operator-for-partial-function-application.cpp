#include <utility>
template<typename Function, typename SecondArgT>
class partial_application_bind2nd_impl {
  public:
  partial_application_bind2nd_impl(Function function, SecondArgT second_arg)
    : function_(function)
    , second_arg_(second_arg) {}

  template<typename FirstArgT>
  auto operator()(FirstArgT&& first_arg) const
  // If you don't have a compiler that supports automatic return type
  // deduction, you need to use decltype to achieve the same effect. Otherwise,
  // you could have written decltype(auto).
  /*-> decltype(function_(std::forward<FirstArgT>(first_arg), second_arg_)) { */
    -> decltype(auto) {
    // The argument of the call operator is passed to the function as the first
    // argument.
    return function_(std::forward<FirstArgT>(first_arg),
    // The save value is passed as the second argument to the function.
      second_arg_);
  }


  private:
  Function function_;
  SecondArgT second_arg_;
};
