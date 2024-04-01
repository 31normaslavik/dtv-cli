# set(Boost_USE_STATIC_LIBS ON) # only find static libs #
# set(Boost_USE_DEBUG_LIBS       ON )  # ignore debug libs and
# set(Boost_USE_RELEASE_LIBS ON) # only find release libs
# set(Boost_USE_MULTITHREADED ON) # set(Boost_USE_STATIC_RUNTIME   OFF)

# find_package(Boost 1.83 REQUIRED COMPONENTS json program_options)
# include_directories(${BOOST_INCLUDE_DIRS})

add_library(jsondata STATIC jsondata.h jsondata.cpp)

target_link_libraries(jsondata PUBLIC Boost::json)

target_include_directories(jsondata PUBLIC .)
