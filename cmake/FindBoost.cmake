set(BOOST_ENABLE_CMAKE ON)

include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
set(BOOST_INCLUDE_LIBRARIES program_options json url)

FetchContent_Declare(
    Boost
    URL https://github.com/boostorg/boost/releases/download/boost-1.86.0/boost-1.86.0-cmake.7z
    USES_TERMINAL_DOWNLOAD TRUE
    GIT_PROGRESS TRUE
    URL_HASH SHA256=ee6e0793b5ec7d13e7181ec05d3b1aaa23615947295080e4b9930324488e078f
    DOWNLOAD_EXTRACT_TIMESTAMP ON
    EXCLUDE_FROM_ALL
    FIND_PACKAGE_ARGS COMPONENTS ${BOOST_INCLUDE_LIBRARIES}
)
FetchContent_MakeAvailable(Boost)

message("Boost_LIBRARIES : ${Boost_LIBRARIES}")
message("BOOST_INCLUDE_LIBRARIES: ${BOOST_INCLUDE_LIBRARIES}")
message("Boost_INCLUDE_DIRS : ${Boost_INCLUDE_DIRS}")
message("Boost_FOUND : ${Boost_FOUND}")

list(TRANSFORM BOOST_INCLUDE_LIBRARIES PREPEND "Boost::")
message("BOOST_INCLUDE_LIBRARIES after transform: ${BOOST_INCLUDE_LIBRARIES}")
