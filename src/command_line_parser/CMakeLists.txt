add_library(cmdlineparser STATIC command_line_parser.cpp command_line_parser.h)

include_directories("${CMAKE_SOURCE_DIR}/src/command")

target_link_libraries(cmdlineparser PRIVATE Boost::program_options commandline)

target_include_directories(cmdlineparser PUBLIC .)
