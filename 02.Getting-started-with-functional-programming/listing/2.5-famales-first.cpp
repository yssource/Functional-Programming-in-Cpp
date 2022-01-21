#include <algorithm>
#include <iostream>
#include <string_view>
#include <vector>

enum class gender {
  male,
  female
};

struct person {
  std::string_view name;
  gender gender;
};

bool is_female(person const& person) {
  return person.gender == gender::female;
}

int main() {
  std::vector<person> people {
    { "Peter", gender::male },
    { "Martha", gender::female },
    { "Jane", gender::female },
    { "David", gender::male },
    { "Rose", gender::female },
    { "Tom", gender::male }
  };
  std::partition(
    people.begin(), people.end(),
    is_female
  );
  for (auto person : people) {
    std::cout << person.name << ' '
      << (person.gender == gender::male ? "male" : "female") << std::endl;
  }
}
