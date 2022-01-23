#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <ostream>
#include <istream>

using namespace std::placeholders;

class person_t {
  public:
  enum class output_format_t {
    name_only,
    full_name
  };

  auto name() const -> std::string;
  auto surname() const -> std::string;
};

auto print_person(person_t const& person,
  std::ostream& out, person_t::output_format_t format) {
  if (format == person_t::output_format_t::name_only) {
    out << person.name() << '\n';
  } else if (format == person_t::output_format_t::full_name) {
    out << person.name() << ' ' << person.surname() << '\n';
  }
}

template<typename Function>
auto make_curried(Function);

int main() {
  person_t martha;

  using std::cout;

  auto print_person_cd{ make_curried(print_person) };

  // All of these write the martha name and surname to the standard output.
  // You can choose how many arguments to provide in the single call.
  print_person_cd(martha, cout, person_t::output_format_t::full_name);
  print_person_cd(martha)(cout, person_t::output_format_t::full_name);
  print_person_cd(martha, cout)(person_t::output_format_t::full_name);
  print_person_cd(martha)(cout)(person_t::output_format_t::full_name);

  auto print_martha{ print_person_cd(martha); };
  print_martha(cout, person_t::output_format_t::name_only);

  // Returns a function object that can print martha's info to the standard
  // output with the format you choose
  auto print_martha_to_cout{ print_person_cd(martha, cout) };
  print_martha_to_cout(person_t::output_format_t::name_only);
}
