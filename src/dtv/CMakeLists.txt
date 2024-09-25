
add_subdirectory(commandline)
add_subdirectory(downloader)
add_subdirectory(engine)
add_subdirectory(extractor)
add_subdirectory(formater)
add_subdirectory(version)
add_subdirectory(video)


add_executable(dtv-cli main.cpp)
target_include_directories(dtv-cli PRIVATE include)

message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")
message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")

target_link_libraries(dtv-cli PRIVATE commandline_parser downloader engine)

include(GNUInstallDirs)
install(
    TARGETS dtv-cli
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
