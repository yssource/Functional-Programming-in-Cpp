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

int main() {
  std::vector<person_t> people;
  extern std::istream file;

  std::for_each(people.cbegin(), people.cend(),
    std::bind(print_person,
      // Creates a unary function that prints the name of a person to the
      // standard output
      _1, std::ref(std::cout), person_t::output_format_t::name_only));

  std::for_each(people.cbegin(), people.cend(),
    std::bind(print_person,
      // Prints the name and the surname of a person to the specified file
      _1, std::ref(file), person_t::output_format_t::full_name));
}
