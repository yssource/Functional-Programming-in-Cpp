#include <type_traits>

// General case: assumes an arbitrary type doesn't
// have a nested value_type type definition
template<typename C,
         typename = std::void_t<>>
struct has_value_type : std::false_type {};

template<typename C>                                        // Specialized case: conisdered
struct has_value_type<C,                                    // only if typename C::value_
                      std::void_t<typename C::value_type>>  // type is an existing type (if
  : std::true_type {};                                      // C has a nested value_type)