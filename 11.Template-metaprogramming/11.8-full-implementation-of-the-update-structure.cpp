#include <type_traits>
template<typename Member, typename Value>
struct update {
  update(Member member, Value value) 
    : member(member)
    , value(value) {
  }

  template<typename Record>
  bool operator()(Record& record) {
    // If the Member callable
    // object returns a bool
    // when you pass it a record
    // and a new value, you
    // have a setter function
    // that might fail.
    if constexpr(std::is_invocable_r<
      bool, Member, Record, Value>()) {
      return std::invoke(member, record, value);
    
    // If the result type isn't
    // bool or convertible to
    // bool, invoke the setter
    // function and return true.
    } else if constexpr(std::is_invocable<
      Member, Record, Value>()) {
      std::invoke(member, record, value);
      return true;

    // If you have a pointer to a member
    // variable, set it and return true.
    } else {
      std::invoke(member, record) = value;
      return true;
    }
  }

  Member member;
  Value value;
};