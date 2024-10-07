
set(CMAKE_FIND_PACKAGE_SORT_ORDER NATURAL)
set(CMAKE_FIND_PACKAGE_SORT_DIRECTION DEC)
set(FETCHCONTENT_QUIET FALSE)

if(CMAKE_VERSION VERSION_GREATER_EQUAL 3.24.0)
	set(DOWN_LD_EX_TI "DOWNLOAD_EXTRACT_TIMESTAMP ON")
	set(FND_PKG "FIND_PACKAGE_ARGS NAMES fmt")
endif()

include(FetchContent)
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG        0c9fce2ffefecfdce794e1859584e25877b7b592 # 11.0.2
  USES_TERMINAL_DOWNLOAD TRUE
  ${DOWN_LD_EX_TI}
  EXCLUDE_FROM_ALL
  INACTIVITY_TIMEOUT 30
  ${FND_PKG}
)
FetchContent_MakeAvailable(fmt)
