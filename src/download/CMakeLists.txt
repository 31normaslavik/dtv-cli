add_library(
  downloader STATIC dataloader.cpp dataloader.h downloader.cpp downloader.h
                    downloadingmedia.cpp downloadingmedia.h)

target_link_libraries(
  downloader
  PRIVATE
  interface jsondata)

target_include_directories(downloader PUBLIC .)
