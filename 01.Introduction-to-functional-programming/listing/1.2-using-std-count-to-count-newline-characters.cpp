#include <algorithm>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>
#include <iostream>

auto count_lines(std::string const& filename) -> int {
  std::ifstream in(filename);

  // Counts newlines from the current position in the stream until the end of
  // the file.
  return std::count(std::istreambuf_iterator<char>(in),
    std::istreambuf_iterator<char>(),
    '\n');
}

auto count_lines_in_files(std::vector<std::string>& files) -> std::vector<int> {
  std::vector<int> results;

  for (auto const& file : files) {
    results.push_back(count_lines(file));
  }

  return results;
}

auto main(int argc, char* argv[]) -> int {
  std::vector<std::string> files;

  while (*++argv != nullptr) {
    files.push_back(*argv);
  }

  auto results = count_lines_in_files(files);
  for (auto const& result : results) {
    std::cout << result << std::endl; 
  }
}
