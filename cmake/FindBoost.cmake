if(UNIX)
    set(Boost_USE_STATIC_LIBS ON) # only find static libs
    #set(Boost_USE_DEBUG_LIBS OFF) # ignore debug libs and
    set(Boost_USE_RELEASE_LIBS ON) # only find release libs
    set(Boost_USE_MULTITHREADED ON)
    #set(Boost_USE_STATIC_RUNTIME OFF)
endif()

# if(MSVC) set(BOOST_JSON_NO_LIB ON) endif()

if(MSVC)
    set(BOOST_ROOT C:/local/boost-1_86)
endif()

# cmake_policy(SET CMP0167 OLD)
find_package(Boost REQUIRED COMPONENTS program_options json url)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
else()
    message(FATAL_ERROR "Boost not found!")
    return()
endif()
