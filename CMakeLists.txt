cmake_minimum_required(VERSION 3.22)
# cmake_policy(VERSION ${CMAKE_VERSION})

project(
    dtv-cli
    VERSION 2.0.2
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
if(CMAKE_CXX_PLATFORM_ID STREQUAL Linux AND (CMAKE_CXX_COMPILER_ID STREQUAL Clang OR CMAKE_CXX_COMPILER_ID STREQUAL GNU))
    set(CMAKE_LINKER_TYPE LLD)
    message("Current linker: ${CMAKE_LINKER_TYPE}")
    message("CMAKE_LINKER_TYPE: ${CMAKE_LINKER_TYPE}")
endif()

# include(cmake/CheckCompiler.cmake)
include(cmake/CheckDir.cmake)
include(cmake/FindFMT.cmake)
include(cmake/FindBoost.cmake)

add_subdirectory(src bin)
add_subdirectory(tests bin-tests EXCLUDE_FROM_ALL)

# include(cmake/RunCheckTest.cmake)

message("CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
message("CMAKE_CXX_COMPILER: ${CMAKE_CXX_COMPILER}")
