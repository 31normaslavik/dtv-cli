# set(Boost_USE_STATIC_LIBS ON) # only find static libs #
# set(Boost_USE_DEBUG_LIBS       ON )  # ignore debug libs and
# set(Boost_USE_RELEASE_LIBS ON) # only find release libs
# set(Boost_USE_MULTITHREADED ON) # set(Boost_USE_STATIC_RUNTIME   OFF)

# find_package(Boost 1.83 REQUIRED COMPONENTS program_options)
# include_directories(${BOOST_INCLUDE_DIRS})

add_library(cmdlineparser STATIC command_line_parser.cpp command_line_parser.h)

target_link_libraries(cmdlineparser PUBLIC Boost::program_options)

target_include_directories(cmdlineparser PUBLIC .)
