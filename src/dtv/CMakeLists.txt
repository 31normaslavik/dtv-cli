
include_directories(include/)


add_subdirectory(commandline)
add_subdirectory(downloader)
add_subdirectory(engine)
add_subdirectory(extractor)
add_subdirectory(formater)
add_subdirectory(version)
add_subdirectory(video)
add_subdirectory(debug)

add_executable(dtv-cli main.cpp)

target_link_libraries(dtv-cli PRIVATE commandline_parser downloader engine debug_t)

include(GNUInstallDirs)
install(
    TARGETS dtv-cli
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
