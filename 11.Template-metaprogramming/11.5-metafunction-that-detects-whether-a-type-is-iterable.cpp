#include <type_traits>

template<typename C,                //
         typename = std::void_t<>>  // The general case: assumes an
struct is_iterable                  // arbitrary type isn't iterable
  : std::false_type {};             //

template<typename C>                                        // Specialized case: conisidered
struct is_iterable<                                         // only if C is iterable, and if its
  C, std::void_t<decltype(*std::begin(std::declval<C>())),  // begin iterator can be
                 decltype(std::end(std::declval<C>()))>>    // dereferenced
  : std::true_type {};                                      //