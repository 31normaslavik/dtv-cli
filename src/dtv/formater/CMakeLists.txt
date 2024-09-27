add_library(formater STATIC formater.cpp)
target_link_libraries(formater PRIVATE commandline video)
target_include_directories(formater PUBLIC ./include)
