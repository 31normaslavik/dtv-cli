add_library(formater STATIC formater.cpp)
target_link_libraries(formater PUBLIC commandline video)
target_include_directories(formater PUBLIC include/)
