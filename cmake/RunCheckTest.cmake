enable_testing()    
add_test(
  NAME mytest
  COMMAND $<TARGET_FILE:${PROJECT_NAME}$<$<PLATFORM_ID:Darwin>:_darwin>$<$<PLATFORM_ID:Windows>:.exe>>
  WORKING_DIRECTORY $<TARGET_FILE_DIR:${PROJECT_NAME}$<$<PLATFORM_ID:Darwin>:_darwin>$<$<PLATFORM_ID:Windows>:.exe>>)

  set_property(TEST mytest PROPERTY
  PASS_REGULAR_EXPRESSION "Options;General;Filesystem;Verbosity;Video;Audio;Subtitle;Network;Debug"
)
