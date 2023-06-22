cmake_minimum_required(VERSION 3.16)

project(ctest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)
# aux_source_directory(src src_dir)
file(GLOB src_dir ${CMAKE_SOURCE_DIR}/src/*.cpp)
list(APPEND src_dir "good")
message(STATUS "The src files: ${src_dir}")
foreach(file ${src_dir})
    message(STATUS ${file})
endforeach()
add_subdirectory(src)


enable_testing()
add_subdirectory(test)
