cmake_minimum_required(VERSION 3.24)

project(dtv-cli LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(Boost_USE_STATIC_LIBS        ON)  # only find static libs
set(Boost_USE_DEBUG_LIBS        OFF)  # ignore debug libs and
set(Boost_USE_RELEASE_LIBS       ON)  # only find release libs
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost 1.83 REQUIRED COMPONENTS json)
include_directories(${BOOST_INCLUDE_DIRS})

add_executable(dtv-cli main.cpp
    presentation.h
    command.h
    interface.h)

target_link_libraries(dtv-cli PRIVATE Boost::json)

include(GNUInstallDirs)
install(TARGETS dtv-cli
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
