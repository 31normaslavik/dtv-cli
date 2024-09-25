cmake_minimum_required(VERSION 3.25)

project(
    dtv-cli
    VERSION 2.0.2
    LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

try_run(run_result compile_result
${CMAKE_BINARY_DIR}/test_output
${CMAKE_SOURCE_DIR}/src/dtv/test_output/main.cpp
RUN_OUTPUT_VARIABLE output)
message(STATUS "run_result: ${run_result}")
message(STATUS "compile_result: ${compile_result}")
message(STATUS "output: " ${output})

#if(UNIX #[[AND ${CMAKE_BUILD_TYPE} STREQUAL "Debug"]])
    # set(CMAKE_CXX_FLAGS
    #     "${CMAKE_CXX_FLAGS} -Wall -Wextra -W -Wshadow -Waddress -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings -Wconversion -Wredundant-decls -Warray-bounds=1 -O2"
    # )
    # message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
    # message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
    # set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -W -Wshadow -Waddress -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings -Wconversion -Wredundant-decls")
    # message(STATUS "CMAKE_CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")
#endif()

# if(MSVC)
# set(CMAKE_CXX_FLAGS
#     "${CMAKE_CXX_FLAGS} /Wall /EHsc /sdl")
# message("CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
# endif()

# Âêëþ÷åíèå ãîðÿ÷åé ïåðåçàãðóçêè äëÿ êîìïèëÿòîðîâ MSVC, åñëè ïîääåðæèâàåòñÿ.
# if (POLICY CMP0141)
#   cmake_policy(SET CMP0141 NEW)
#   set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
# endif()

# if(MSVC)
#   #target_compile_options(dtv-cli PUBLIC "/ZI")
#   #target_link_options(dtv-cli PUBLIC "/INCREMENTAL")
# endif()
include(cmake/CheckDir.cmake)
include(cmake/FindBoost.cmake)
add_subdirectory(src bin)
#add_subdirectory(test EXCLUDE_FROM_ALL)
