add_library(debug_t STATIC debug.cpp)
target_include_directories(debug_t PUBLIC include/)
target_link_libraries(debug_t PUBLIC fmt::fmt)
