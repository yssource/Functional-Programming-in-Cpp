// In the general case, remove_reference<T>::type
// is type T: it returns the same type it gets.
template<typename T>
struct remove_reference {
  using type = T;
};

// If you get an lvalue reference T&,
// strip the reference and return T.
template<typename T>
struct remove_reference<T&> {
  using type = T;
};

// If you get an rvalue reference T&&,
// strip the reference and return T.
template<typename T>
struct remove_reference<T&&> {
  using type = T;
};