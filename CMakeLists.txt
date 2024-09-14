cmake_minimum_required(VERSION 3.10.0)

project(dtv-cli VERSION 2.0.2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(LINUX AND ${CMAKE_BUILD_TYPE} STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -W -Wshadow -Waddress -Wpointer-arith -Wcast-qual -Wcast-align -Wwrite-strings -Wconversion -Wredundant-decls -Warray-bounds=1 -O2")
    message(STATUS "CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
    message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")
endif()

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

add_subdirectory(src)
add_subdirectory(test)

