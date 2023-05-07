cmake_minimum_required(VERSION 3.16)

project(ctest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

add_subdirectory(src)


enable_testing()
add_subdirectory(test)
