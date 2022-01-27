#include <algorithm>

auto& operator++() {
  // Iterator to the collection you're filtering. When the proxy iterator is to
  // be incremented, find the first element after the current one that satisfies
  // the predicate.
  +current_position_;
  current_position_ = 
    // Starts the search from the next element
    std::find_if(current_position_,
      // If no more element satisfy the predicate, returns an iterator pointing
      // to the end of the source collection, which is also the end of the filtered
      // range
      end_,
      predicate_);
}
