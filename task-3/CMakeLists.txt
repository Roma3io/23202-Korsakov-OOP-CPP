cmake_minimum_required(VERSION 3.29)
project(task_3)

set(CMAKE_CXX_STANDARD 20)

add_executable(task_3 main.cpp)

set_target_properties(task_3 PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/WAV_FILES)
include_directories(src)
add_subdirectory(src)

target_link_libraries(task_3 ${CMAKE_PROJECT_NAME}_lib)
