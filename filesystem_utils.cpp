#include <files/filesystem_utils.hpp>
#include <files/third_party/portable-file-dialogs.h>
#include <string>

std::string select_file() {
  auto selection = pfd::open_file("Select a file").result();
  if (!selection.empty()) {
    std::cout << "User selected file " << selection[0] << "\n";
    std::cout << "------------------\n";
    return selection[0];
  }
  return "";
}
std::string select_dir() { return ""; }
