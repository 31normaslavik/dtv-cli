add_library(merge STATIC mergevideofile.cpp mergevideofile.h)

include_directories("${CMAKE_SOURCE_DIR}/src/download")

target_link_libraries(
  merge
  PUBLIC presentation fs_directories
  interface downloadingmedia)

target_include_directories(merge PUBLIC .)
