#ifndef SCANNER_HPP
#define SCANNER_HPP
#include "filesystem_utils.hpp"
#include <filesystem>
#include <string>
#include <vector>
namespace fs = std::filesystem;

class Scanner {
public:
  std::vector<fs::path> scan(const std::string &dir);
};
#endif // !SCANNER_HPP
