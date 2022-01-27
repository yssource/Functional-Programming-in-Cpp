auto operator*() const {
  // Gets the value from the original collection, applies the transformation
  // function to it, and returns it as the value the proxy iterator points to
  return function_(*current_position_);
}
