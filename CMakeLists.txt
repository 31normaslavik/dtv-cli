cmake_minimum_required(VERSION 3.24)

project(dtv-cli LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost 1.82 REQUIRED COMPONENTS json)
include_directories(${BOOST_INCLUDE_DIRS})

add_executable(dtv-cli main.cpp)

target_link_libraries(dtv-cli PRIVATE Boost::json)

include(GNUInstallDirs)
install(TARGETS dtv-cli
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
