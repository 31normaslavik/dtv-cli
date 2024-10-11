set(CMAKE_FIND_PACKAGE_SORT_ORDER NATURAL)
set(CMAKE_FIND_PACKAGE_SORT_DIRECTION DEC)
set(FETCHCONTENT_QUIET FALSE)
set(BOOST_ENABLE_CMAKE ON)
set(FETCHCONTENT_TRY_FIND_PACKAGE_MODE NEVER)

find_package(Boost 1.81 COMPONENTS program_options json url)
if(Boost_FOUND)
  message(STATUS "Found Boost version: ${Boost_VERSION}")
else()
  message(STATUS "Boost not found and will be downloaded from git")
  
  include(FetchContent)
  
  FetchContent_Declare(
    Boost
    URL https://github.com/boostorg/boost/releases/download/boost-1.86.0/boost-1.86.0-cmake.7z
    URL_HASH SHA256=ee6e0793b5ec7d13e7181ec05d3b1aaa23615947295080e4b9930324488e078f # 1.86
    USES_TERMINAL_DOWNLOAD TRUE
    DOWNLOAD_EXTRACT_TIMESTAMP ON
    EXCLUDE_FROM_ALL
    INACTIVITY_TIMEOUT 30
  )

FetchContent_MakeAvailable(Boost)

endif()

