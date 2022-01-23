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

  auto print(std::ostream& out, output_format_t format) const -> void {
    if (format == output_format_t::name_only) {
      out << name() << '\n';
    } else if (format == output_format_t::full_name) {
      out << name() << ' ' << surname() << '\n';
    }
  }

  auto name() const -> std::string;
  auto surname() const -> std::string;
};



int main() {
  std::vector<person_t> people;
  extern std::istream file;

  std::for_each(people.cbegin(), people.cend(),
    // You're creating a unary function object from a member function pointer.
    std::bind(&person_t::print,
      _1, std::ref(std::cout), person_t::output_format_t::name_only));

  std::for_each(people.cbegin(), people.cend(),
    std::bind(&person_t::print,
      _1, std::ref(file), person_t::output_format_t::full_name));
}
