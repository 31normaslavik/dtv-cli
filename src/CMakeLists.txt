# cmake_minimum_required(VERSION 3.20)

# project(dtv-cli LANGUAGES CXX)

# set(CMAKE_CXX_STANDARD 23) set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Boost_USE_STATIC_LIBS ON) # only find static libs
# set(Boost_USE_DEBUG_LIBS       ON )  # ignore debug libs and
set(Boost_USE_RELEASE_LIBS ON) # only find release libs
set(Boost_USE_MULTITHREADED ON)
# set(Boost_USE_STATIC_RUNTIME   OFF)

find_package(Boost 1.83 REQUIRED COMPONENTS json program_options)
include_directories(${BOOST_INCLUDE_DIRS})

add_library(downloader STATIC downloader.cpp downloader.h fs_directories.cpp
                              fs_directories.h
                              mergevideofile.h mergevideofile.cpp
                              downloadingmedia.h downloadingmedia.cpp
                              dataloader.h dataloader.cpp)

add_library(presentation STATIC presentation.cpp presentation.h)

add_library(commandline STATIC commandline.cpp commandline.h)

add_executable(dtv-cli main.cpp)

add_subdirectory(interface)
add_subdirectory(jsondata)
add_subdirectory(command_line_parser)

target_link_libraries(dtv-cli PRIVATE downloader commandline presentation)
target_link_libraries(dtv-cli PRIVATE cmdlineparser)
target_link_libraries(
  dtv-cli
  PUBLIC
  interface jsondata)

include(GNUInstallDirs)
install(
  TARGETS dtv-cli
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
