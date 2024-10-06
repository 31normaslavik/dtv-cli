include(FetchContent)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG        0c9fce2ffefecfdce794e1859584e25877b7b592 # 11.0.2
  USES_TERMINAL_DOWNLOAD TRUE
  DOWNLOAD_EXTRACT_TIMESTAMP ON
  EXCLUDE_FROM_ALL
  INACTIVITY_TIMEOUT 30
  FIND_PACKAGE_ARGS NAMES fmt
)
FetchContent_MakeAvailable(fmt)
