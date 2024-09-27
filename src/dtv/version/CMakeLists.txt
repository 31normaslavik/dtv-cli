configure_file(version.cpp.in src/dtv/version/version.cpp @ONLY)
add_library(version STATIC ${CMAKE_CURRENT_BINARY_DIR}/src/dtv/version/version.cpp)
target_include_directories(version PUBLIC ./include)
