add_library(extractor STATIC extractor.cpp)
target_link_libraries(extractor PRIVATE video commandline)
target_include_directories(extractor PUBLIC ./include)
