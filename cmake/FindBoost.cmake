set(BOOST_ENABLE_CMAKE ON)

set(CMAKE_FIND_PACKAGE_SORT_ORDER NATURAL)
set(CMAKE_FIND_PACKAGE_SORT_DIRECTION DEC)
set(FETCHCONTENT_QUIET FALSE)
set(BOOST_INCLUDE_LIBRARIES program_options json url)

find_package(Boost 1.82 COMPONENTS program_options json url)
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
else()

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



message("Boost_LIBRARIES : ${Boost_LIBRARIES}")
message("Boost_INCLUDE_DIRS : ${Boost_INCLUDE_DIRS}")

list(TRANSFORM BOOST_INCLUDE_LIBRARIES PREPEND "Boost::")
message("BOOST_INCLUDE_LIBRARIES after transform: ${BOOST_INCLUDE_LIBRARIES}")
