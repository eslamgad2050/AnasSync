#ifndef FILESYSTEM_UTILS_HPP
#define FILESYSTEM_UTILS_HPP

#include <files/third_party/portable-file-dialogs.h>
#include <filesystem>
#include <string>

namespace fs = std::filesystem;

class MyFile {
  std::string path;
  std::uint64_t size;
  std::time_t last_modified_time;

public:
  MyFile(const std::string &path_to_file);
  std::string get_modification_date();
};
std::string select_file();
std::string select_dir();
std::string select_file_or_dir();

#endif // !FILESYSTEM_UTILS
