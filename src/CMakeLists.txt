cmake_minimum_required(VERSION 3.24.2)

if(LINUX)
    set(Boost_USE_STATIC_LIBS ON) # only find static libs
    #set(Boost_USE_DEBUG_LIBS OFF) # ignore debug libs and
    set(Boost_USE_RELEASE_LIBS ON) # only find release libs
    set(Boost_USE_MULTITHREADED ON)
    #set(Boost_USE_STATIC_RUNTIME OFF)
endif()

# if(MSVC) set(BOOST_JSON_NO_LIB ON) endif()

if(MSVC)
    set(BOOST_INCLUDEDIR C:/Boost/include/boost-1_85)
    set(BOOST_LIBRARYDIR C:/Boost/lib)
endif()

find_package(Boost 1.75 REQUIRED COMPONENTS program_options json url)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    message("Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
else()
    message("Boost not found!")
    return()
endif()

add_library(downloader STATIC
    command_line_parser.cpp command_line_parser.h
    commandline.cpp         commandline.h
    downloader.cpp          downloader.h
    extractor.cpp           extractor.h
    fs_directories.cpp      fs_directories.h
    video.cpp               video.h
    formater.cpp            formater.h
    engine.cpp              engine.h
                            debug.h
                            helper.h
)

configure_file(version.cpp.in version.cpp @ONLY)
add_library(version STATIC ${CMAKE_CURRENT_BINARY_DIR}/version.cpp version.h)

add_executable(dtv-cli main.cpp)

message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")

target_link_libraries(dtv-cli PRIVATE downloader ${Boost_LIBRARIES})
target_link_libraries(dtv-cli PRIVATE version)

target_include_directories(downloader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(version PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

include(GNUInstallDirs)
install(
    TARGETS dtv-cli
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
