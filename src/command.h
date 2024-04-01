#pragma once

#include <filesystem>
#include <iostream>

void get_file_size(const std::filesystem::directory_entry& entry) {
  std::cout << entry.path().filename() << " "
              << std::filesystem::file_size(entry.path().filename()) / 1024
              << " KiB" << std::endl;
}






