#include <functional>
#include <list>
namespace detail {
  template<
    typename Sender,
    typename SourceMessageT =
      typename Sender::value_type,
    typename MessageT =
      typename SourceMessageT::value_type>
  class join_impl {
  public:
    using value_type = MessageT;

    void process_message(SourceMessageT&& source) {
      // When you get a new stream to listen to, store
      // it, and forward its messages as your own.
      sources_.emplace_back(std::move(source));
      sources_.back().set_message_handler(emit_);
    }

  private:
    Sender sender_;
    std::function<void(MessageT&&)> emit_;
    // Saves all the streams you listen to, to expand their
    // lifetimes. Uses a list to minimize the number of
    // reallocations.
    std::list<SourceMessageT> sources_;
  };
}