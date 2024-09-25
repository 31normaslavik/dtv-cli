add_library(video STATIC video.cpp)
target_include_directories(video PUBLIC include)
target_link_libraries(video PRIVATE Boost::json)
