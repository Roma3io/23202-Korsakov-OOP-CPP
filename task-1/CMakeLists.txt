cmake_minimum_required(VERSION 3.29)
project(task_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(BitArray BitArray.cpp)
target_include_directories(BitArray PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
#add_subdirectory(Google_tests)
