add_library(commandline STATIC commandline.cpp commandline.h)

include_directories("${CMAKE_SOURCE_DIR}/src/presentation")

target_link_libraries(commandline PUBLIC presentation)

target_include_directories(commandline PUBLIC .)
