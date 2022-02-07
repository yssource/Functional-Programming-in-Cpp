#include <tuple>
#include <type_traits>

template<typename Function, typename... CapturedArgs>
class curried {
private:
  using captured_args_tuple_t =
    std::tuple<std::decay_t<CapturedArgs>...>;
  
  template<typename... Args>
  static auto capture_by_copy(Args&&... args) {
    return std::tuple<std::decay_t<Args>...>(
      std::forward<Args>(args)...);
  }

public:
  curried(Function function, CapturedArgs... args)
    : function_(function)
    , captured_(capture_by_copy(std::move(args)...)) {
  }

  curried(Function function, std::tuple<CapturedArgs...> args)
    : function_(function)
    , captured_(capture_by_copy(std::move(args))) {
  }

  template<typename... NewArgs>
  auto operator()(NewArgs&&... args) const {
    auto new_args{ capture_by_copy(     // Creates a tuple out of
      std::forward<NewArgs>(args)...)}; // the new arguments
    
    auto all_args{ std::tuple_cat(      // Concatenates the previously collected
      captured_, std::move(new_args))}; // arguments with the new ones

    if constexpr(std::is_invocable_v<Function,  // If you can call function_ with
      CapturedArgs..., NewArgs...>) {           // the given arguments, do so.
      return std::apply(function_, all_args);   //
    } else {
      return curried<Function,  //
        CapturedArgs...,        // Otherwise, return a new curried instance
        NewArgs...>(            // with all the arguments so far stored insider.
        function_, all_args);   //
    }
  }
  
private:
  Function function_;
  std::tuple<CapturedArgs...> captured_;
};