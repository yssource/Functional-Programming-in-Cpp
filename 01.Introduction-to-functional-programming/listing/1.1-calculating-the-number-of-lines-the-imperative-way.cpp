#include <fstream>
#include <iostream>
#include <string>
#include <vector>

auto count_lines_in_files(std::vector<std::string>& files) -> std::vector<int> {
  std::vector<int> results;
  char c{ 0 };

  for (auto const& file : files) {
    int line_count{ 0 };
    std::ifstream in(file);

    while (in.get(c)) {
      if (c == '\n') {
        ++line_count;
      }
    }

    results.push_back(line_count);
  }

  return results;
}

auto main(int argc, char* argv[]) -> int {
  std::vector<std::string> files;
  while (*++argv != NULL) {
    files.push_back(*argv);
  }

  std::vector<int> results{ count_lines_in_files(files) };
  for (auto const& result : results) {
    std::cout << result << std::endl;
  }
}
