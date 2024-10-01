cmake_minimum_required(VERSION 3.29)
project(task_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(main main.cpp)

set_target_properties(main PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

#include_directories(src)
#add_subdirectory(src)
#
#add_subdirectory(Google_tests)
#
#target_link_libraries(word_count ${CMAKE_PROJECT_NAME}_lib)