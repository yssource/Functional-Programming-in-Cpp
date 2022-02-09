#include <functional>
template<typename Sender,
         typename Predicate,
         // You're receiving the same type of message you're sending.
         typename MessageT =
           typename Sender::value_type>
class filter_impl {
public:
  using value_type = MessageT;

  // ...

  void process_message(MessageT&& message) const {
    // When you receive a message, checks whether
    // it satisfies the predicate, and if so passes it on
    if (std::invoke(predicate_, message)) {
      emit_(std::move(message));
    }
  }

private: 
  Sender sender_;
  Predicate predicate_;
  std::function<void(MessageT&&)> emit_;
};