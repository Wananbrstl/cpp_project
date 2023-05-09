cmake_minimum_required(VERSION 3.10)

project(GameMath)

set(CMAKE_CXX_FLAGS "-std=c++17 -Wall")
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib/)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/)

add_subdirectory(src)

enable_testing()
add_subdirectory(test)
