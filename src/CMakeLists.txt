set(Boost_USE_STATIC_LIBS ON) # only find static libs
#set(Boost_USE_DEBUG_LIBS OFF) # ignore debug libs and
#set(Boost_USE_RELEASE_LIBS ON) # only find release libs
#set(Boost_USE_MULTITHREADED ON)
#set(Boost_USE_STATIC_RUNTIME OFF)

# if(MSVC) set(BOOST_JSON_NO_LIB ON) endif()

if(MSVC)
  set(BOOST_INCLUDEDIR C:/Boost/include/boost-1_85)
  set(BOOST_LIBRARYDIR C:/Boost/lib)    
endif()

find_package(Boost 1.70 REQUIRED COMPONENTS program_options json url)

if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
  message("Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
  #add_executable(foo foo.cc)
  #target_link_libraries(foo ${Boost_LIBRARIES})
endif()

add_library(downloader STATIC
    command_line_parser.cpp
    commandline.cpp
    dataloader.cpp
    downloader.cpp
    downloadingmedia.cpp
    extractor.cpp
    fs_directories.cpp
    mergevideofile.cpp
    video.cpp
    videosource.cpp
    formater.h formater.cpp
    debug.h
    #[[version.h
    version.cpp]])

configure_file(version.cpp.in version.cpp @ONLY)
add_library(version STATIC ${CMAKE_CURRENT_BINARY_DIR}/version.cpp version.h)

add_executable(dtv-cli main.cpp)

message("CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")

target_link_libraries(dtv-cli PUBLIC downloader Boost::program_options Boost::json Boost::url)
target_link_libraries(dtv-cli PUBLIC version)

target_include_directories(downloader PUBLIC .)
target_include_directories(version PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

message("projectName_VERSION: ${PROJECT_NAME}")

include(GNUInstallDirs)
install(
  TARGETS dtv-cli
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
