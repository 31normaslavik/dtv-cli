add_library(video STATIC video.cpp)
target_link_libraries(video PRIVATE Boost::json)
target_include_directories(video PUBLIC ./include)
