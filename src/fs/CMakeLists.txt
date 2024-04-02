add_library(fs_directories fs_directories.cpp fs_directories.h)

# target_link_libraries(interface PUBLIC Boost::json)

target_include_directories(fs_directories PUBLIC .)
