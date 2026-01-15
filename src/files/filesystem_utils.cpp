#include "portable-file-dialogs.h"
#include <chrono>
#include <ctime>
#include <exception>
#include <files/filesystem_utils.hpp>
#include <filesystem>
#include <iostream>
#include <string>
std::string select_file() {
  try {
    auto selection = pfd::open_file("Select a file").result();
    if (!selection.empty()) {
      return selection[0];
    }
  } catch (const std::exception &e) {
    std::cout << "error while selecting file dialog ---------------" << e.what()
              << "\n";
    return "";
  }
  return "";
}

std::string select_dir() {
  try {
    auto selection = pfd::select_folder("Select a folder").result();
    if (!selection.empty()) {
      if (!std::filesystem::exists(selection)) {
        std::cout << "the selected dir is not exit\n";
        return "";
      } else if (!std::filesystem::is_directory(selection)) {
        std::cout << "the selected dir is not valid\n";
        return "";
      }
      return selection;
    }
  } catch (const std::exception &e) {
    std::cout << "error while selecting dir dialog ---------------" << e.what()
              << "\n";
    return "";
  }
  return "";
}

std::string select_file_or_dir() {

  auto dialog_type =
      pfd::message("Selection Type",
                   "What would you like to select?\n\n"
                   "Yes = Select a FILE\n"
                   "No = Select a FOLDER\n"
                   "Cancel = Go back",
                   pfd::choice::yes_no_cancel, pfd::icon::question)
          .result();
  if (dialog_type == pfd::button::yes) {
    return select_file();
  } else if (dialog_type == pfd::button::no) {
    return select_dir();
  } else {
    return "";
  }
}

MyFile::MyFile(const std::string &path_to_file) : path(path_to_file) {

  size = fs::file_size(path_to_file);
  auto time = fs::last_write_time(path_to_file);
  auto t = std::chrono::time_point_cast<std::chrono::system_clock::duration>(
      time - std::filesystem::file_time_type::clock::now() +
      std::chrono::system_clock::now());
  last_modified_time = std::chrono::system_clock::to_time_t(t);
}

std::string MyFile::get_modification_date() {
  std::tm *ltime = std::localtime(&last_modified_time);
  char buffer[20];
  std::strftime(buffer, sizeof(buffer), "%d/%m/%Y %H:%M:%S", ltime);
  std::cout << "the file is modified at " << buffer << "\n";
  return buffer;
}
