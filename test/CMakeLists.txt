cmake_minimum_required(VERSION 3.29)

project(dtv-cli-test LANGUAGES CXX)

enable_testing()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        Ia5eed4bec26da8c8cbe29fbd3a41b44048c25e07 # release-1.15.2
  FIND_PACKAGE_ARGS NAMES GTest
)
FetchContent_MakeAvailable(googletest)


if ($ENV{GOOGLETEST_DIR})
    get_filename_component(_GTEST_BASE $ENV{GOOGLETEST_DIR} REALPATH)
elseif (EXISTS "") # set by QC
    get_filename_component(_GTEST_BASE "" REALPATH) # set by QC
endif()

if (NOT GTEST_ROOT)
    if (_GTEST_BASE)
        message("Setting GTEST_ROOT to ${_GTEST_BASE}")
        set(GTEST_ROOT ${_GTEST_BASE})
    else()
        message("No GTEST_ROOT specified - using system defaults.")
    endif()
endif()


find_package(GTest REQUIRED)
if (NOT GTest_FOUND)
    message (FATAL_ERROR "No GTest Found")
endif()

add_executable(dtv-cli-test main.cpp tst_extractor.cpp
    tst_initfs.cpp
)
add_test(NAME dtv-cli-test COMMAND dtv-cli-test)

target_link_libraries(dtv-cli-test PRIVATE GTest::GTest PUBLIC downloader)
if (GMock_FOUND)
    target_link_libraries(dtv-cli-test INTERFACE GTest::GMock)
endif()
