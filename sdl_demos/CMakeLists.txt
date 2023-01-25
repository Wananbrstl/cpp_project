cmake_minimum_required(VERSION 3.10)
project(SDL_DEMO01)


set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")

find_package(SDL3 REQUIRED)
include_directories(${SDL3_INCLUDE_DIRS})

add_executable(main src/demo01.cpp)
target_link_libraries(main ${SDL3_LIBS})
