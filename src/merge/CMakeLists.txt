add_library(merge STATIC mergevideofile.cpp mergevideofile.h)

target_link_libraries(merge PRIVATE fs_directories video)

target_include_directories(merge PUBLIC .)
