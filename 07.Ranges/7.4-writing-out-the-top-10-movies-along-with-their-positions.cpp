#include <algorithm>
#include <string>
#include <iostream>
#include <range.h>

using namespace ranges::v3;

template<typename Range>
void write_top_10(Range const& xs) {
  auto items{
    // Zips the range of movies with the range of integers, starting with 1.
    // This gives a range of pairs: a movie name and the index.
    view::zip(xs, view::ints(1))
      | view::transform([](auto const& pair) {
      // The transform function takes a pair and generates a string containing
      // the rank of the movie and the movie name.
          return std::to_string(pair.second) +
              " " + pair.first;
        })
      // You're interested in the first 10 movies.
      | view::take(10);
  };

  std::for_each(items.cbegin(), items.cend(), [](auto const& item) {
    std::cout << item << std::endl;
  });
}
