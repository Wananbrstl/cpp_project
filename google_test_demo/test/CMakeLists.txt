cmake_minimum_required(VERSION 3.10)

find_package(GTest REQUIRED)
include_directories(../include/)
include_directories(${GTEST_INCLUDE_DIR})

add_executable(test_sum test_sum.cpp ../src/sum.cpp)

target_link_libraries(test_sum GTest::gtest GTest::gtest_main)

