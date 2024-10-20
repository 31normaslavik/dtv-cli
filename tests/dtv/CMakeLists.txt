cmake_minimum_required(VERSION 3.29)

project(dtv-cli-test LANGUAGES CXX)

enable_testing()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# include(FetchContent) FetchContent_Declare( googletest GIT_REPOSITORY
# https://github.com/google/googletest.git GIT_TAG
# Ia5eed4bec26da8c8cbe29fbd3a41b44048c25e07 # release-1.15.2 FIND_PACKAGE_ARGS
# NAMES GTest ) FetchContent_MakeAvailable(googletest)

if($ENV{GOOGLETEST_DIR})
  get_filename_component(_GTEST_BASE $ENV{GOOGLETEST_DIR} REALPATH)
elseif(EXISTS "") # set by QC
  get_filename_component(_GTEST_BASE "" REALPATH) # set by QC
endif()

if(NOT GTEST_ROOT)
  if(_GTEST_BASE)
    message("Setting GTEST_ROOT to ${_GTEST_BASE}")
    set(GTEST_ROOT ${_GTEST_BASE})
  else()
    message("No GTEST_ROOT specified - using system defaults.")
  endif()
endif()

find_package(GTest REQUIRED)
if(NOT GTest_FOUND)
  message(FATAL_ERROR "No GTest Found")
endif()

add_executable(dtv-cli-test main.cpp tst_extractor.cpp tst_initfs.cpp
                            tst_changetempdir.cpp)

add_dependencies(dtv-cli-test jsonsdir)

add_test(NAME dtv-cli-test COMMAND dtv-cli-test)

target_link_libraries(
  dtv-cli-test
  PRIVATE GTest::GTest
  PRIVATE downloader video fs)

if(GMock_FOUND)
  target_link_libraries(dtv-cli-test INTERFACE GTest::GMock)
endif()

include(GoogleTest)
gtest_discover_tests(dtv-cli-test)

message("CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
message("CMAKE_CURRENT_BINARY_DIR: ${CMAKE_CURRENT_BINARY_DIR}")

message(
  STATUS
    "copying ${CMAKE_CURRENT_SOURCE_DIR}/jsons to ${CMAKE_CURRENT_BINARY_DIR}/")

add_custom_target(
  jsonsdir
  # COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/jsons
  COMMAND ${CMAKE_COMMAND} -E copy_directory jsons ${CMAKE_CURRENT_BINARY_DIR}/jsons
  COMMENT "copying ${CMAKE_CURRENT_SOURCE_DIR}/jsons to ${CMAKE_CURRENT_BINARY_DIR}/jsons"
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
