#include <cassert>
#include <memory>
#include "9.2-types-to-denote-different-states.cpp"

class program_t {
public:
  program_t()
  // The initial state should be an
  // instance of init_t. state_
  // should never be null.
    : state_(std::make_unique<init_t>()) {}

  void counting_finished() {
    // If counting is finished, it should mean
    // you were in the couting state. If you
    // can't guarantee this assumprion holds,
    // you can use if-else instead of assert.
    assert(state_->type == running_t::id);

    // You know the exact type of the
    // class state_ points to, so you
    // can statically cast to it.
    auto state = static_cast<running_t*>(state_.get());

    // Switches to the new state that
    // holds the end result. The previous
    // state is destroyed.
    state_ = std::make_unique<finished_t>(state->count());
  }

private:
  std::unique_ptr<state_t> state_;
};