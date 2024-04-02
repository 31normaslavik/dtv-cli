add_library(jsondata STATIC jsondata.h jsondata.cpp)

target_link_libraries(jsondata PUBLIC Boost::json)

target_include_directories(jsondata PUBLIC .)
