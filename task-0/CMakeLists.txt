cmake_minimum_required(VERSION 3.29)
project(task_0)

set(CMAKE_CXX_STANDARD 20)

add_executable(word_count word_count.cpp)

set_target_properties(word_count PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})

include_directories(src)
add_subdirectory(src)

add_subdirectory(Google_tests)


target_link_libraries(word_count ${CMAKE_PROJECT_NAME}_lib)