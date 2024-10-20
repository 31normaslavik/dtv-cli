
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

add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E rename ${PROJECT_NAME}$<$<PLATFORM_ID:Windows>:.exe> ${PROJECT_NAME}$<$<PLATFORM_ID:Darwin>:_darwin>$<$<PLATFORM_ID:Windows>:.exe>
  COMMAND ${CMAKE_COMMAND} -E sha256sum ${PROJECT_NAME}$<$<PLATFORM_ID:Darwin>:_darwin>$<$<PLATFORM_ID:Windows>:.exe> > ${PROJECT_NAME}$<$<PLATFORM_ID:Darwin>:_darwin>$<$<PLATFORM_ID:Windows>:.exe>.sha256sum
  COMMAND ${CMAKE_COMMAND} -E sha512sum ${PROJECT_NAME}$<$<PLATFORM_ID:Darwin>:_darwin>$<$<PLATFORM_ID:Windows>:.exe> > ${PROJECT_NAME}$<$<PLATFORM_ID:Darwin>:_darwin>$<$<PLATFORM_ID:Windows>:.exe>.sha512sum
  WORKING_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}>
  VERBATIM)

if(EXISTS ${CMAKE_BINARY_DIR}/compile_commands.json)
  message(STATUS "copying compile_commands.json to ${CMAKE_SOURCE_DIR}")

  add_custom_command(
  TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy -t ${CMAKE_SOURCE_DIR} compile_commands.json
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  COMMENT "copying compile_commands.json to ${CMAKE_SOURCE_DIR}"
  VERBATIM)

endif()

include(GNUInstallDirs)
install(
    TARGETS dtv-cli
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

    

       
