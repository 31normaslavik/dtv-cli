add_library(
  downloader STATIC dataloader.cpp dataloader.h downloader.cpp downloader.h
                    downloadingmedia.cpp downloadingmedia.h)

target_include_directories(downloader PUBLIC .)
