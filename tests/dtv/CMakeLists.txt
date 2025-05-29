cmake_minimum_required(VERSION 3.29)

project(dtv-cli-test LANGUAGES CXX)

enable_testing()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_COMPILER_LINKER lld)



include(FetchContent)
  if(CMAKE_VERSION VERSION_LESS 3.24)
    FetchContent_Declare(
      GTest
      URL https://github.com/google/googletest/releases/download/v1.15.2/googletest-1.15.2.tar.gz
      URL_HASH SHA256=7b42b4d6ed48810c5362c265a17faebe90dc2373c885e5216439d37927f02926
      USES_TERMINAL_DOWNLOAD TRUE
      EXCLUDE_FROM_ALL
      INACTIVITY_TIMEOUT 30)
else()
    FetchContent_Declare(
      GTest
      URL https://github.com/google/googletest/releases/download/v1.15.2/googletest-1.15.2.tar.gz
      URL_HASH SHA256=7b42b4d6ed48810c5362c265a17faebe90dc2373c885e5216439d37927f02926
      USES_TERMINAL_DOWNLOAD TRUE
      DOWNLOAD_EXTRACT_TIMESTAMP ON
      EXCLUDE_FROM_ALL
      INACTIVITY_TIMEOUT 30)
endif()
FetchContent_MakeAvailable(GTest)

add_executable(dtv-cli-test main.cpp tst_extractor.cpp tst_initfs.cpp
                            tst_changetempdir.cpp)

add_dependencies(dtv-cli-test jsonsdir)
add_test(NAME dtv-cli-test COMMAND dtv-cli-test)

target_link_libraries(
  dtv-cli-test
  PRIVATE GTest::gtest GTest::gmock downloader video fs)

#include(GoogleTest)
#gtest_discover_tests(dtv-cli-test)

message(STATUS "copying ${CMAKE_CURRENT_SOURCE_DIR}/jsons to ${CMAKE_CURRENT_BINARY_DIR}/")

add_custom_target(
  jsonsdir
  COMMAND ${CMAKE_COMMAND} -E copy_directory jsons ${CMAKE_CURRENT_BINARY_DIR}/jsons
  COMMENT "copying ${CMAKE_CURRENT_SOURCE_DIR}/jsons to ${CMAKE_CURRENT_BINARY_DIR}/jsons"
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
