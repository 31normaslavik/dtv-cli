cmake_minimum_required(VERSION 3.22...3.30.2)
message("CMAKE_VERISON: ${CMAKE_VERSION}")
message("CMAKE_MINIMUM_REQUIRED_VERSION: ${CMAKE_MINIMUM_REQUIRED_VERSION}")

# if (${CMAKE_VERSION} VERSION_LESS 3.22)
#   cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
# endif ()

message("CMAKE_VERISON: ${CMAKE_VERSION}")

project(
    dtv-cli
    VERSION 2.0.2
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# include(cmake/CheckCompiler.cmake)
message("CMAKE_VERSION ${CMAKE_VERSION}")

include(cmake/CheckDepedencies.cmake)
include(cmake/FindFMT.cmake)
include(cmake/CheckDir.cmake)
include(cmake/FindBoost.cmake)
# include(cmake/FindYtDlp.cmake)
add_subdirectory(src bin)

#add_subdirectory(test EXCLUDE_FROM_ALL)
