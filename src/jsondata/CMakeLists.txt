add_library(jsondata_c STATIC jsondata.h jsondata.cpp)

target_link_libraries(jsondata_c PRIVATE Boost::json)

target_include_directories(jsondata_c PUBLIC .)
