#include <functional>
#include <utility>
namespace detail {
  template<typename Sender,
           typename Function,
           typename MessageT = typename Sender::value_type>
  class sink_impl {
  public:
    sink_impl(Sender&& sender, Function function)
      : sender_(std::move(sender))
      , function_(function) {
      // When the sink in constructed,
      // it connects to its assigned
      // sender automatically.
      sender_.set_message_handler(
        [this](MessageT&& message) {
          process_message(std::move(message));
        }
      );
    }

    void process_message(MessageT&& message) const {
      // When you get a message, you pass it
      // on to the function defined by the user.
      std::invoke(function_,
        std::move(message));
    }

  private:
    Sender sender_;
    Function function_;
  };
}