try_run(run_result compile_result
  ${CMAKE_BINARY_DIR}/test_output
  ${CMAKE_SOURCE_DIR}/src/dtv/test_output/main.cpp
  RUN_OUTPUT_VARIABLE output)

#message(STATUS "run_result: ${run_result}")
message(STATUS "compile_result: ${compile_result}")
#message(STATUS "output: " ${output})

if(NOT compile_result)
  message(SEND_ERROR "Unsuitable compiler")
endif()
