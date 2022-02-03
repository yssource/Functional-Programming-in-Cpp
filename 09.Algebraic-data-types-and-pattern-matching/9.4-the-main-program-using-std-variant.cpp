#include <cassert>
#include <variant>

class socket_t {};

class init_t {
};

class running_t {
public:
  unsigned count() const {
    return count_;
  }

private:
  unsigned count_ = 0;
  socket_t web_page;
};

class finished_t {
public:
  finished_t(unsigned count)
    : count_(count) {}
  
  unsigned count() const {
    return count_;
  }

private:
  unsigned count_;
};

class program_t {
public:
  program_t()
  // Initially, the state is an
  // instance of init_t.
    : state_(init_t()) {}

  void counting_finished() {
    // Uses std::get_if to check
    // whether there's a value
    // of a specified type in
    // std::variant. Returns
    // nulptr if the variant
    // doesn't hold the value of
    // the specified type.
    auto* state = std::get_if<running_t>(&state_);
    assert(state != nullptr);

    // Changing the current state is as easy as
    // assigning the new value to the variable.
    state_ = finished_t(state->count());
  }

private:
  std::variant<init_t, running_t, finished_t> state_;
};