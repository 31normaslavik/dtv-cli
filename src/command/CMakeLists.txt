add_library(commandline STATIC commandline.cpp commandline.h
    helper.h)

add_library(cmdlineparser STATIC command_line_parser.cpp command_line_parser.h)

target_link_libraries(cmdlineparser PRIVATE Boost::program_options commandline)

target_include_directories(cmdlineparser PUBLIC .)
