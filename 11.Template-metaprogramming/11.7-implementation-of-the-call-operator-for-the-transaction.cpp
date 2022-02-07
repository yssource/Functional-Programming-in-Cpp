#include <algorithm>

template<typename Record>
class transaction {
public:
  transaction(Record& record)
    : record_(record) {
  }

  template<typename... Updates>
  bool operator()(Updates... updates) {
    // Creates a temporary copy to
    // perform updates on
    auto temp{ record_ };

    // Applies all the updates. If all updates
    // are usccessful, swaps the temporary
    // copy with the original record and
    // returns true.
    if (all(updates(temp)...)) {
      std::swap(record_, temp);
      return true;
    }

    return false;
  }

private:
  template<typename... Updates>
  // Collects all the results of different updates,
  // and returns true if all of them succeeded
  bool all(Updates... results) const {
    return (... && results);
  }

  Record& record_;
};