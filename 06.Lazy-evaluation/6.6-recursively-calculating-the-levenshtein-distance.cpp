#include <algorithm>

// Skips passing the strings a and b as parameters, for clarity
auto lev(unsigned m, unsigned n) -> unsigned {
  // If either string is empty, the distance is the length of the other one.
  return m == 0 ? n
       : n == 0 ? m
       : std::min({
       // Counts the operation of adding a character
          lev(m - 1, n) + 1,
       // Counts the operation of removing a character
          lev(m, n - 1) + 1,
       // Counts the operation of replacing a character, but only if you haven't
       // replaced a character with the same one
          lev(m - 1, n - 1) + (a[m - 1] != b[n - 1])
        });
}
