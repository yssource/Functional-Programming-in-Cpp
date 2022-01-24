#include <algorithm>
#include <string>
class person_t {
public:
  // This member function will work on normal values and lvalue references.
  person_t with_name(std::string const& name) const & {
    // Creates a copy of the person
    person_t result(*this);

    // Sets the new name for that person. It's OK to change the name because
    // this person_t instance still isn't visible from the outside world.
    result.name_ = name;

    // Returns the newly created person_t instance. From this point on, it's
    // immutable.
    return result;
  }

  // This one will be called on temporaries and other rvalue references.
  person_t with_name(std::string const& name) && {
    // Calls the move constructor instead of the copy constructor
    person_t result(std::move(*this));

    // Sets the name
    result.name_ = name;

    // Returns the newly created person
    return result;
  }

private:
  std::string name_;
};
