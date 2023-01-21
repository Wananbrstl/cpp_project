###############################################
#File: project_source_dir/CMakeLists.txt 
###############################################

cmake_minimum_required(VERSION 3.10)

project(lbn_json)

set("CMAKE_CXX_FLAGS" " -g -std=c++11 -Wall")
set(${EXECUTABLE_OUTPUT_PATH} bin)

include_directories(include)
add_subdirectory(test)
