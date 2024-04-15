add_library(downloader STATIC downloader.cpp downloader.h)
add_library(dataloader STATIC dataloader.cpp dataloader.h)
add_library(downloadingmedia STATIC downloadingmedia.cpp downloadingmedia.h)

include_directories("${CMAKE_SOURCE_DIR}/src/command")
include_directories("${CMAKE_SOURCE_DIR}/src/fs")
include_directories("${CMAKE_SOURCE_DIR}/src/interface")
include_directories("${CMAKE_SOURCE_DIR}/src/jsondata")
include_directories("${CMAKE_SOURCE_DIR}/src/merge")

target_link_libraries(
  dataloader
  PUBLIC fs_directories commandline
  interface jsondata)

target_link_libraries(downloadingmedia PUBLIC fs_directories commandline)

target_link_libraries(downloader PUBLIC merge downloadingmedia dataloader)

target_include_directories(downloader PUBLIC .)
