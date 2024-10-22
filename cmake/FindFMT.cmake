set(CMAKE_FIND_PACKAGE_SORT_ORDER NATURAL)
set(CMAKE_FIND_PACKAGE_SORT_DIRECTION DEC)
set(FETCHCONTENT_QUIET FALSE)

message(STATUS "fmt not found and will be downloaded from git")
include(FetchContent)
if(CMAKE_VERSION VERSION_LESS 3.24)
  FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG        2cb3b7c64b04fd99b700dc1a40cc5115da549359 # 11.0.2
    USES_TERMINAL_DOWNLOAD TRUE
    EXCLUDE_FROM_ALL
    INACTIVITY_TIMEOUT 30)
else()
  FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG        2cb3b7c64b04fd99b700dc1a40cc5115da549359 # 11.0.2
    USES_TERMINAL_DOWNLOAD TRUE
    DOWNLOAD_EXTRACT_TIMESTAMP ON
    EXCLUDE_FROM_ALL
    INACTIVITY_TIMEOUT 30)
endif()
FetchContent_MakeAvailable(fmt)
