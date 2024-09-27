add_library(commandline STATIC commandline.cpp)
add_library(commandline_parser STATIC commandline_parser.cpp)
add_library(fs STATIC fs.cpp)

target_include_directories(commandline PUBLIC include/commandline ../include)
target_include_directories(commandline_parser PUBLIC include/commandline ../include)
target_include_directories(fs PUBLIC ./include ../include)

target_link_libraries(commandline PUBLIC fs PRIVATE Boost::url)
target_link_libraries(commandline_parser PRIVATE commandline version Boost::program_options)

