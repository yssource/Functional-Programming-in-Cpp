#include <mutex>

class employment_history_t {
  public:
  auto loaded() const -> bool;
};

class person_t {
public:
  auto load_employment_history() const -> void;

  employment_history_t employment_history() const {
    // Locks the mutex to guarantee that a concurrent invocation of
    // employment_history can't be executed until you finish retrieving the data
    // from the database
    std::unique_lock<std::mutex> lock{ employment_history_mutex_ };

    // Gets the data if it isn't already loaded
    if (!employment_history_.loaded()) {
      load_employment_history();
    }

    // The data is loaded; you're returning it to the caller.
    return employment_history_;
  }

private:
  // You want to be able to lock the mutex from a constant member function, so
  // it needs to be mutable as well as the variable you're initializing.
  mutable std::mutex employment_history_mutex_;
  mutable employment_history_t employment_history_;
};
