set(Boost_USE_STATIC_LIBS ON) # only find static libs
# set(Boost_USE_DEBUG_LIBS       ON )  # ignore debug libs and
set(Boost_USE_RELEASE_LIBS ON) # only find release libs
set(Boost_USE_MULTITHREADED ON)
# set(Boost_USE_STATIC_RUNTIME   OFF)

find_package(Boost 1.8 REQUIRED COMPONENTS json program_options)
include_directories(${BOOST_INCLUDE_DIRS})

add_executable(dtv-cli main.cpp)

add_subdirectory(interface)
add_subdirectory(jsondata)
add_subdirectory(command_line_parser)
add_subdirectory(command)
add_subdirectory(download)
add_subdirectory(fs)
add_subdirectory(merge)
add_subdirectory(presentation)

target_link_libraries(dtv-cli PRIVATE downloader commandline presentation
                                      cmdlineparser fs_directories)

include(GNUInstallDirs)
install(
  TARGETS dtv-cli
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
