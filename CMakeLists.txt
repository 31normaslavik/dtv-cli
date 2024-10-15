cmake_minimum_required(VERSION 3.22...3.30.2)
cmake_policy(VERSION ${CMAKE_VERSION})

project(
    dtv-cli
    VERSION 2.0.2
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# include(cmake/CheckCompiler.cmake)
include(cmake/CheckDir.cmake)
include(cmake/CheckDepedencies.cmake)
include(cmake/FindFMT.cmake)
include(cmake/FindBoost.cmake)
# include(cmake/FindYtDlp.cmake)
add_subdirectory(src bin)

#add_subdirectory(test EXCLUDE_FROM_ALL)
