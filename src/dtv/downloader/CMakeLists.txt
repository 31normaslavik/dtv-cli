add_library(downloader STATIC downloader.cpp)
target_link_libraries(downloader PRIVATE commandline engine extractor)
target_include_directories(downloader PUBLIC include)
