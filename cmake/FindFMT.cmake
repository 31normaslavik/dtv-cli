
set(CMAKE_FIND_PACKAGE_SORT_ORDER NATURAL)
set(CMAKE_FIND_PACKAGE_SORT_DIRECTION DEC)
set(FETCHCONTENT_QUIET FALSE)

find_package(fmt 9.1)
if(fmt_FOUND)
  message(STATUS "fmt found version: ${fmt_VERSION}")
else()
  message(STATUS "fmt not found and will be downloaded from git")

  include(FetchContent)
    FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG        2cb3b7c64b04fd99b700dc1a40cc5115da549359 # 11.0.2
    USES_TERMINAL_DOWNLOAD TRUE
    DOWNLOAD_EXTRACT_TIMESTAMP ON
    EXCLUDE_FROM_ALL
    INACTIVITY_TIMEOUT 30
    )
  FetchContent_MakeAvailable(fmt)

  message(STATUS "fmt version is now: ${fmt_VERSION}")
endif()
