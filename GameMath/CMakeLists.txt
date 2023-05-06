cmake_minimum_required(VERSION 3.10)

project(GameMath)

set(CMAKE_CXX_FLAGS "-std=c++11 -Wall")
set(LIBRARY_OUTPUT_PATH ./lib/)

find_package(GTest REQUIRED)

include_directories(./include/)
include_directories(${GTEST_INCLUDE_DIRS})

# add_subdirectory(./3rd_party/)

add_library(gamemath SHARED src/Vec3d.cpp)
set(google_test /usr/local/lib/libgtest.a)

enable_testing()
add_executable(main src/main.cpp)

target_link_libraries(main gamemath pthread ${google_test})
add_test(test_all main)
