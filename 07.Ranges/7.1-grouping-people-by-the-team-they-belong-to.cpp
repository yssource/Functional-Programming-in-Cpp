#include <iterator>
#include <vector>
#include <string>
#include <algorithm>

template<typename Persons, typename F>
auto group_by_team(Persons& persons, F team_for_person, std::vector<std::string>& teams) {
  auto begin{ std::begin(persons) };
  auto const end{ std::end(persons) };

  std::for_each(teams.cbegin(), teams.cend(),
    [&](auto const& team) {
      begin = std::partition(begin, end,
        [&](auto const& person) {
          return team == team_for_person(person);
      });
  });
}
