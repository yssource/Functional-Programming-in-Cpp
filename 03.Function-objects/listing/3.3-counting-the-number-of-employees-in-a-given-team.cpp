#include <algorithm>
#include <string>
#include <vector>

class person_t;

class company_t {
public:
  std::string team_name_for(person_t const& employee) const;

  int count_team_members(std::string const& team_name) const;

private:
  std::vector<person_t> employee_;
};

int company_t::count_team_members(const std::string &team_name) const {
  return std::count_if(
    employee_.cbegin(), employee_.cend(),
    // You need to capture "this" because you're implicitly using it when
    // calling the team_name_for member function, and you've captured team_name
    // because you need to use it for comparison.
    [this, &team_name]
    // As before, this function object has only one argument: an employee.
    // You'll return whether they belong to the specified team.
      (person_t const& employee) {
      return team_name_for(employee) == team_name;
    });
}
