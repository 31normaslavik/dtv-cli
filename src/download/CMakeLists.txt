add_library(downloader STATIC downloader.cpp downloader.h)
add_library(dataloader STATIC dataloader.cpp dataloader.h)
add_library(downloadingmedia STATIC downloadingmedia.cpp downloadingmedia.h)

target_link_libraries(dataloader PRIVATE video jsondata_c presentation)

target_link_libraries(downloader PRIVATE merge downloadingmedia dataloader)

target_include_directories(downloader PUBLIC .)
target_include_directories(
  dataloader
  PRIVATE ../command
  PUBLIC ../fs ../video)
target_include_directories(
  downloadingmedia
  PRIVATE ../fs ../video
  PUBLIC ../command)
