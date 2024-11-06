cmake_minimum_required(VERSION 3.29)
project(task_2)

set(CMAKE_CXX_STANDARD 20)

add_executable(main main.cpp)

include_directories(src)
add_subdirectory(src)


target_link_libraries(main ${CMAKE_PROJECT_NAME}_lib)