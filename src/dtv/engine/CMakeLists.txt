add_library(engine STATIC engine.cpp)
target_link_libraries(engine PUBLIC video commandline_parser PRIVATE formater
    "$<$<VERSION_LESS_EQUAL:$<CXX_COMPILER_VERSION>,12.4.0>:fmt::fmt>")
target_include_directories(engine PUBLIC include/)
