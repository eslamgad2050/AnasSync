#include <cstddef>
#include <ios>
#include <memory>
#include <string>
#define XXH_STATIC_LINKING_ONLY // For XXH3 functions
#define XXH_IMPLEMENTATION
#include <files/Hasher.hpp>
#include <files/third_party/xxhash.h>
#include <fstream>
#include <iostream>
#include <vector>
std::string Hasher::hash_file(std::string file_path) {
  std::shared_ptr<std::fstream> file = std::make_shared<std::fstream>();
  file->open(file_path, std::ios::binary | std::ios::in | std::ios::ate);
  if (!*file) {
    std::cout << "error! :could not open file in " << file_path << std::endl;
    return "";
  }
  size_t file_size = file->tellg();
  if (file_size < 1) {
    std::cout << "file_size <1";
    return "";
  } else if (file_size < 1024 * 1024 * 100) {
    return hash_small_file(file, file_size);
  } else {
    return hash_large_file(file, file_size);
  }
}
std::string Hasher::hash_small_file(std::shared_ptr<std::fstream> file,
                                    std::size_t file_size) {
  file->seekg(0);
  std::vector<char> buffer(file_size);
  file->read(buffer.data(), file_size);
  if (buffer.empty()) {
    std::cout << "the buffer is empty";
    return "";
  }
  auto hash = XXH3_128bits(buffer.data(), file_size);
  char hex[33];
  snprintf(hex, sizeof(hex), "%016llX%016llX", (unsigned long long)hash.high64,
           (unsigned long long)hash.low64);
  return std::string(hex);
}

std::string Hasher::hash_large_file(std::shared_ptr<std::fstream> file,
                                    std::size_t file_size) {
  XXH3_state_t *state = XXH3_createState();
  XXH3_128bits_reset(state);
  file->seekg(0);
  std::size_t buffer_size = 65536;
  std::vector<char> buffer(buffer_size);
  while (file->read(buffer.data(), buffer_size) || file->gcount() > 0) {
    XXH3_128bits_update(state, buffer.data(), buffer_size);
  }
  auto hash = XXH3_128bits_digest(state);
  XXH3_freeState(state);
  char hex[33];
  snprintf(hex, sizeof(hex), "%016llX%016llX", (unsigned long long)hash.high64,
           (unsigned long long)hash.low64);
  return std::string(hex);
}
