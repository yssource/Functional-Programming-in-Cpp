#include <algorithm>
#include <vector>
#include <iostream>
#include "3.1-creating-a-function-object-with-a-generic-call-operator.cpp"

class person {
  int age_;
public:
  person(int age) : age_(age) {}
  int age() const { return age_; }

};

class project {
  int age_;
public:
  project(int age) : age_(age) {}
  int age() const { return age_; }
};

class car {
  int age_;
public:
  car(int age) : age_(age) {}
  int age() const { return age_; }
};

int main() {

  std::vector<person> persons{ 55, 3, 22, 16 };
  std::vector<car> cars{ 55, 3, 22, 16 };
  std::vector<project> projects{ 55, 3, 22, 16 };

  older_than predicate(5);
  std::cout << std::count_if(persons.cbegin(), persons.cend(), predicate)
    << ' ' << std::count_if(cars.cbegin(), cars.cend(), predicate)
    << ' ' << std::count_if(projects.cbegin(), projects.cend(), predicate)
    << '\n';
}
