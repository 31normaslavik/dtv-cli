add_library(
  interface STATIC
  video.cpp
  video.h
  videoyoutube.cpp
  videoyoutube.h
  videovimeo.cpp
  videovimeo.h
  videoninegag.cpp
  videoninegag.h
  interface.h)

# target_link_libraries(interface PUBLIC Boost::json)

target_include_directories(interface PUBLIC .)
