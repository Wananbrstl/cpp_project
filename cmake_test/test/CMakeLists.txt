find_package(GTest REQUIRED)
add_executable(test_sum test1.cpp)
target_link_libraries(test_sum mysum GTest::gtest pthread)
add_test(
    NAME test_sum
    COMMAND test_sum
)
