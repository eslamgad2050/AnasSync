// #include "asio/io_context.hpp"
// #include <exception>
// #include <thread>
#include <asio.hpp>
#include <files/Hasher.hpp>
#include <files/Scanner.hpp>
#include <files/filesystem_utils.hpp>
#include <files/third_party/portable-file-dialogs.h>
#include <iostream>
#include <network/netwrokManager.h>
#include <string>
int main() {
  try {
    auto selection = select_file_or_dir();
    if (!selection.empty()) {
      std::cout << "User selected file " << selection << "\n";
      std::cout << "------------------\n";
      Scanner scaner;
      scaner.scan(selection);
      Hasher hasher;
      std::cout << "the file hash is" << hasher.hash_file(selection);
    } else {
      std::cout << "no selection\n";
    }
  } catch (const std::exception &e) {
    std::cout << "erro ecured : \n-----------------" << e.what()
              << "\n----------------------------";
  }
  return 0;
}

// fstream file;
// file.open(selection[0], ios::in | ios::out);
// if (!file) {
//   cout << "file is not open\n";
// }
// string xx;
// file.seekg(0);
// while (getline(file, xx)) {
//   cout << xx;
// }
// file.close();
// return 0;
//
// try {
//   asio::io_context context;
//   UDP_server UD(context);
//   std::thread th([&context] { context.run(); });
//   cout << "no error\n";
//   int x;
//   cout << "what you want to do "
//           "\n1) for scan\n"
//        << std::endl;
//   cin >> x;
//   switch (x) {
//   case 1:
//     cout << "\nscaning\n";
//     UD.scan(context);
//
//     break;
//   case 2:
//     break;
//   default:
//     break;
//     break;
//   }
//   th.join();
// } catch (exception &e) {
//   cerr << e.what() << endl;
//   cout << "error";
// }
// cout << "program ended";
// return 0;
// }
