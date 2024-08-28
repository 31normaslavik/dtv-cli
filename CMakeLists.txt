cmake_minimum_required(VERSION 3.24.2)

project(dtv-cli VERSION 2.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(LINUX)
set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS}
    -Wall                     \
    -Werror                   \
    -Wextra                   \
    -pedantic                 \
    -Wcast-align              \
    -Wcast-qual               \
    -Wctor-dtor-privacy       \
    -Wdisabled-optimization   \
    -Wformat=2                \
    -Winit-self               \
    -Wlogical-op              \
    -Wmissing-include-dirs    \
    -Wmissing-declarations    \
    -Wnoexcept                \
    -Wold-style-cast          \
    -Woverloaded-virtual      \
    -Wredundant-decls         \
    -Wshadow                  \
    -Wsign-promo              \
    -Wstrict-null-sentinel    \
    -Wstrict-overflow=5       \
    -Wundef                   \
    -Wno-unused               \
    -Wno-variadic-macros      \
    -Wno-parentheses          \
    -fdiagnostics-show-option")
message("CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
endif()

if(MSVC)
set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} /Wall /EHsc /sdl")
message("CMAKE_CXX_FLAGS: ${CMAKE_CXX_FLAGS}")
endif()

# Âêëþ÷åíèå ãîðÿ÷åé ïåðåçàãðóçêè äëÿ êîìïèëÿòîðîâ MSVC, åñëè ïîääåðæèâàåòñÿ.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

if(MSVC)
  #target_compile_options(dtv-cli PUBLIC "/ZI")
  #target_link_options(dtv-cli PUBLIC "/INCREMENTAL")
endif()

add_subdirectory(src)
add_subdirectory(test)

