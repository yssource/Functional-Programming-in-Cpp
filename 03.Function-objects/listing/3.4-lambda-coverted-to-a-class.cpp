#include <string>
#include "3.3-counting-the-number-of-employees-in-a-given-team.cpp"

class lambda_implementation {
public:
  lambda_implementation(company_t const* _this, std::string const& team_name)
    : this_(_this)
    , team_name_(team_name) {}

  bool operator()(person_t const& employee) const {
    return this_->team_name_for(employee) == team_name_;
  }

private:
  company_t const* this_;
  std::string const& team_name_;
};
