add_library(video STATIC video.cpp video.h videosource.h videosource.cpp
    extractor.h extractor.cpp)
target_link_libraries(video PRIVATE Boost::url Boost::json)

target_include_directories(video PUBLIC .)
