// greater : (double, double) → bool
bool greater(double first, double second) {
  return first > second;
}

// greater_curried : double → (double → bool)
auto greater_curried(double first) {
  return [first](double second) {
    return first > second;
  };
}

int main() {
  // Invocation
  
  // Returns false
  greater(2, 3);
  // Returns a unary function object that checks whether its argument is less than 2
  greater_curried(2);   
  // Returns false
  greater_curried(2)(3);
}
