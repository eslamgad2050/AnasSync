#include <files/Scanner.hpp>
#include <filesystem>
#include <iostream>
#include <vector>
std::vector<fs::path> Scanner::scan(const std::string &dir) {

  std::vector<fs::path> files;
  if (!fs::exists(dir) || !fs::is_directory(dir)) {
    std::cout << "\nerror:\n------- the dier is not exist----------\n";
    return files;
  }
  for (const auto x : fs::recursive_directory_iterator(dir)) {
    try {
      if (x.is_regular_file()) {
        std::cout << "file: " << x.path() << "\n";
        files.push_back(x);
      }
    } catch (const fs::filesystem_error e) {
      std::cout << "\nerror:\n" << e.what() << "\n";
      continue;
    }
  }
  return files;
}
