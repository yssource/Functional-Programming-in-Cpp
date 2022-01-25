#include "6.10-structure-that-holds-an-arbitrary-number-of-strings.cpp"
#include <string>
#include <iostream>

lazy_string_concat_helper<> lazy_concat;

int main() {
  std::string name{ "Jane" };
  std::string surname{ "Smith" };

  // You can't overload the operator+ on std::string, so use a small trick to
  // force the use of the concatenation structure by appending to an instance of
  // it.
  std::string const fullname{ lazy_concat + surname + ", " + name };

  std::cout << fullname << std::endl;
}
