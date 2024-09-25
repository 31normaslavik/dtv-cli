add_library(engine STATIC engine.cpp)
target_link_libraries(engine PUBLIC video commandline PRIVATE formater)
target_include_directories(engine PUBLIC include)
