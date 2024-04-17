add_library(video STATIC video.cpp video.h videosource.h videosource.cpp)

target_include_directories(video PUBLIC .)
