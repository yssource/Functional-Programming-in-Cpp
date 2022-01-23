template<typename Function, typename SecondArgT>
class partial_application_on_2nd_impl {
  public:
  partial_application_on_2nd_impl(Function function, SecondArgT second_arg)
    : function_(function)
    , second_arg_(second_arg) {}


  private:
  Function function_;
  SecondArgT second_arg_;
};
