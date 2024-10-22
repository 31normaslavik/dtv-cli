set(CMAKE_FIND_PACKAGE_SORT_ORDER NATURAL)
set(CMAKE_FIND_PACKAGE_SORT_DIRECTION DEC)
set(FETCHCONTENT_QUIET FALSE)
set(BOOST_ENABLE_CMAKE ON)
set(FETCHCONTENT_TRY_FIND_PACKAGE_MODE NEVER)

include(FetchContent)
if(CMAKE_VERSION VERSION_LESS 3.24)
  FetchContent_Declare(
    Boost
    URL https://github.com/boostorg/boost/releases/download/boost-1.86.0/boost-1.86.0-cmake.7z
    URL_HASH SHA256=ee6e0793b5ec7d13e7181ec05d3b1aaa23615947295080e4b9930324488e078f # 1.86
    USES_TERMINAL_DOWNLOAD TRUE      
    EXCLUDE_FROM_ALL
    INACTIVITY_TIMEOUT 30)  
else()
  FetchContent_Declare(
    Boost
    URL https://github.com/boostorg/boost/releases/download/boost-1.86.0/boost-1.86.0-cmake.7z
    URL_HASH SHA256=ee6e0793b5ec7d13e7181ec05d3b1aaa23615947295080e4b9930324488e078f # 1.86
    USES_TERMINAL_DOWNLOAD TRUE
    DOWNLOAD_EXTRACT_TIMESTAMP ON
    EXCLUDE_FROM_ALL
    INACTIVITY_TIMEOUT 30)
endif()
FetchContent_MakeAvailable(Boost)

