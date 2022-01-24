#include <string>
#include <list>
#include <numeric>

class movie_t {
public:
  auto average_score() const -> double;

private:
  std::string name_;
  std::list<int> scores_;
};

auto movie_t::average_score() const -> double {
  // Calling begin and end on a const value is the same as calling cbegin and
  // cend.
  return std::accumulate(scores_.cbegin(), scores_.cend(), 0)
    / static_cast<double>(scores_.size());
}
