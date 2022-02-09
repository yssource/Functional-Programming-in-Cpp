#include <functional>

// An actor can receive messages of
// on type and send messages of
// another.
template<typename SourceMessageT,
         typename MessageT>
class actor {
public:
  // Defines the type of the
  // message the actor is
  // sending, so you can
  // check it later when you
  // need to connect actors
  using value_type = MessageT;

  void process_message(SourceMessageT&& message);

  template<typename EmitF>
  // Sets the emit_ handler
  // the actor calls when it
  // wants to send a message
  void set_message_handler(EmitF emit);
private:
  std::function<void(MessageT&&)> emit_;
};