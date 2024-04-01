add_library(
  interface STATIC
  interface.cpp
  interface.h
  videoyoutube.cpp
  videoyoutube.h
  videovimeo.cpp
  videovimeo.h
  videoninegag.cpp
  videoninegag.h)

# target_link_libraries(interface PUBLIC Boost::json)

target_include_directories(interface PUBLIC .)
