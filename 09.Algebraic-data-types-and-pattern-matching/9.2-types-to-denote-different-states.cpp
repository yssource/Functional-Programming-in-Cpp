#include "9.1-tagged-superclass-for-creating-sum-types-through-inheritance.cpp"

class socket_t {};

class init_t : public state_t {
// The class representing the initial state
// doesn't need to hold any data; you still
// don't have the handler to the web page
// or the counter. It only needs to set the
// type to its ID (zero).
public:
  enum { id = 0 };
  init_t()
    : state_t(id) {}
};

class running_t : public state_t {
public:
  enum { id = 1 };
  running_t()
    : state_t(id) {}

  unsigned count() const {
    return count_;
  }

private:
// For the running state, you need a
// counter and the handler to the web
// page whose you want to count.
  unsigned count_ = 0;
  socket_t web_page;
};

class finished_t : public state_t {
public:
  enum { id = 2 };
// When the counting is finished, you no
// longer need the handler to the web page.
// You only need the calculated value.
  finished_t(unsigned count)
    : state_t(id)
    , count_(count) {}
  
  unsigned count() const {
    return count_;
  }

private:
  unsigned count_;
};