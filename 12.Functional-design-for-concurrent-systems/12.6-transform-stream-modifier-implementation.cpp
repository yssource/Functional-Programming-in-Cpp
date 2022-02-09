#include <functional>
#include <utility>
namespace detail {
  template<
    typename Sender,
    typename Transformation,
    // To properly define the
    // message receiving and
    // sending functions, you need
    // the types of the messages
    // you recive and the type of
    // the messages you send.
    typename SourceMessageT =
      typename Sender::value_type,
    typename MessageT =
      decltype(std::declval<Transformation>()(
        std::declval<SourceMessageT>()))>
  class transform_impl {
  public:
    using value_type = MessageT;

    transform_impl(Sender&& sender, Transformation transformation)
      : sender_(std::move(sender))
      , transformation_(transformation) {
    }

    template<typename EmitF>
    void set_message_handler(EmitF emit) {
      // When an actor is
      // interested in messages,
      // connect to the actor
      // that will send the
      // messages.
      emit_ = emit;
      sender_.set_message_handler(
        [this](SourceMessageT&& message) {
          process_message(
            std::move(message));
        });
    }

    void process_message(SourceMessageT&& message) const {
      // When you receive a
      // message, transform it with
      // the given function and send
      // the result to the actor that
      // listens to you.
      emit_(std::invoke(transformation_,
        std::move(message)));
    }

  private:
    Sender sender_;
    Transformation transformation_;
    std::function<void(MessageT&&)> emit_;
  };
}