#include <algorithm>
#include <iterator>
#include <type_traits>
#include <utility>
#include <vector>

// Initializes type C to be the tyoe of the collection, P1 to be the type of the
// fist item in a pair coming from the source collection (with const removed),
// and P2 to be the type of second item in the pair
template<typename C, typename P1 = typename std::remove_cv<typename C::value_type::first_type>::type, typename P2 = typename C::value_type::second_type>
std::vector<std::pair<P2, P1>> reverse_pairs(C const& items) {
  // and lifts it to a new function that can oerfirn the same task but on
  // multiple items in a collection
  std::vector<std::pair<P2, P1>> result(items.size());

  std::transform(std::begin(items), std::end(items), std::begin(result),
    [](std::pair<P1 const, P2>& p) {
      return std::make_pair(p.second, p.first);
  });
}
