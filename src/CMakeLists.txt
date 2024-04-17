set(Boost_USE_STATIC_LIBS ON) # only find static libs
set(Boost_USE_DEBUG_LIBS OFF) # ignore debug libs and
set(Boost_USE_RELEASE_LIBS ON) # only find release libs
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

# if(MSVC) set(BOOST_JSON_NO_LIB ON) endif()

find_package(Boost REQUIRED COMPONENTS program_options json)
include_directories(${BOOST_INCLUDE_DIRS})

add_executable(dtv-cli main.cpp)

add_subdirectory(command)
add_subdirectory(download)
add_subdirectory(fs)
add_subdirectory(video)
add_subdirectory(jsondata)
add_subdirectory(merge)
add_subdirectory(presentation)

message("CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")

target_link_libraries(dtv-cli PUBLIC downloader commandline video cmdlineparser
                                     fs_directories)

include(GNUInstallDirs)
install(
  TARGETS dtv-cli
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
