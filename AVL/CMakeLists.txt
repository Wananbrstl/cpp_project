# FIX: 需要学习下CMake下的Google Test框架

#####################################
cmake_minimum_required(VERSION 3.10)
project(AVL)

#####################################
set("CMAKE_CXX_FLAGS" "-std=c++14 -Wall")
set(${EXECUTABLE_OUTPUT_PATH} ./bin)

#####################################
find_package(GTest REQUIRED)

#####################################
include_directories(include)
include_directories(${GTEST_INCLUDE_DIRS})

#####################################
enable_testing()

add_executable(AVL_TEST src/AVL.cpp)

#####################################
add_subdirectory(test)

