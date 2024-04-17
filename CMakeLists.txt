cmake_minimum_required(VERSION 3.24.2)

project(dtv-cli LANGUAGES CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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

add_subdirectory(src)
