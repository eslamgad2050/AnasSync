#ifndef HASHER_HPP
#define HASHER_HPP

#include <cstddef>
#include <fstream>
#include <iostream>
#include <memory>
class Hasher {
public:
  Hasher() {}
  std::string hash_file(std::string file_path);

private:
  std::string hash_small_file(std::shared_ptr<std::fstream> file,
                              std::size_t file_size);
  std::string hash_large_file(std::shared_ptr<std::fstream> file,
                              std::size_t file_size);
};
#endif // !HASHER_HPP
