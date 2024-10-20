cmake_minimum_required(VERSION 3.29)

project(dtv-cli-test LANGUAGES CXX)

enable_testing()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#find_package(GTest)
if(GTest_FOUND)
  message(STATUS "Found GTest version: ${GTest_VERSION}")
else()
  message(STATUS "GTest not found and will be downloaded from git")
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
endif()

# if($ENV{GOOGLETEST_DIR})
#   get_filename_component(_GTEST_BASE $ENV{GOOGLETEST_DIR} REALPATH)
# elseif(EXISTS "") # set by QC
#   get_filename_component(_GTEST_BASE "" REALPATH) # set by QC
# endif()

# if(NOT GTEST_ROOT)
#   if(_GTEST_BASE)
#     message("Setting GTEST_ROOT to ${_GTEST_BASE}")
#     set(GTEST_ROOT ${_GTEST_BASE})
#   else()
#     message("No GTEST_ROOT specified - using system defaults.")
#   endif()
# endif()

add_executable(dtv-cli-test main.cpp tst_extractor.cpp tst_initfs.cpp
                            tst_changetempdir.cpp)

add_dependencies(dtv-cli-test jsonsdir)

add_test(NAME dtv-cli-test COMMAND dtv-cli-test)

target_link_libraries(
  dtv-cli-test
  PRIVATE GTest::gtest
  PRIVATE downloader video fs)

if(GMock_FOUND)
  target_link_libraries(dtv-cli-test INTERFACE GTest::gmock)
endif()

include(GoogleTest)
gtest_discover_tests(dtv-cli-test)

message(STATUS "copying ${CMAKE_CURRENT_SOURCE_DIR}/jsons to ${CMAKE_CURRENT_BINARY_DIR}/")

add_custom_target(
  jsonsdir
  COMMAND ${CMAKE_COMMAND} -E copy_directory jsons ${CMAKE_CURRENT_BINARY_DIR}/jsons
  COMMENT "copying ${CMAKE_CURRENT_SOURCE_DIR}/jsons to ${CMAKE_CURRENT_BINARY_DIR}/jsons"
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
