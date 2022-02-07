#include <algorithm>
#include <vector>
#include <string>

template<typename T>
using contained_type_t = decltype(*std::begin(std::declval<T>()));

template<typename T>
class error;

error<contained_type_t<std::vector<std::string>>>();