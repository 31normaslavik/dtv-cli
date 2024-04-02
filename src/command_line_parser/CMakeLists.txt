add_library(cmdlineparser STATIC command_line_parser.cpp command_line_parser.h)

target_link_libraries(cmdlineparser PUBLIC Boost::program_options)

target_include_directories(cmdlineparser PUBLIC .)
