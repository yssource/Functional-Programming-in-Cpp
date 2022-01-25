#include <algorithm>
#include <string>
template<typename... Strings>
class lazy_string_concat_helper;

template<typename LastString, typename... Strings>
class lazy_string_concat_helper<LastString, Strings...> {
private:
  // Stores the copy of the original string
  LastString data_;
  // Stores the structure that contains other strings
  lazy_string_concat_helper<Strings...> tail_;

public:
  lazy_string_concat_helper(LastString data, lazy_string_concat_helper<Strings...> tail)
    : data_(data), tail_(tail) {}

  // Calculates the size of all strings combined
  int size() const {
    return data_.size() + tail_.size();
  }

  template<typename It>
  void save(It end) const {
    // The structure stores strings in reverse order: the data member variable
    // contains the string that coms last, so it needs to go to the end of the
    // buffer.
    auto const begin{ end - data_.size() };
    std::copy(data_.cbegin(), data_.cend(), begin);
    tail_.save(begin);
  }

  operator std::string() const {
    // When you want to convert the expression definition into a real string,
    // allocate enough memory and start copying the strings into it.
    std::string result(size(), '\0');
    save(result.end());
    return result;
  }

  // Creates a new instance of the structure with one string added to it
  auto operator+(std::string const& other) const
    -> lazy_string_concat_helper<std::string, LastString, Strings...> {
    return lazy_string_concat_helper<std::string, LastString, Strings...>(
      other, *this);
  }
};

template<>
class lazy_string_concat_helper<> {
public:
  lazy_string_concat_helper() {}
  int size() const { return 0; }
  template<typename It> void save(It) const {}

  lazy_string_concat_helper<std::string> operator+(std::string const& other) const {
    return lazy_string_concat_helper<std::string>(
      other, *this);
  }
};
