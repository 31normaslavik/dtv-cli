add_library(debug_t STATIC debug.cpp)
target_include_directories(debug_t PUBLIC include/)
target_link_libraries(debug_t PUBLIC "$<$<VERSION_LESS_EQUAL:$<CXX_COMPILER_VERSION>,12.4.0>:fmt::fmt>")
