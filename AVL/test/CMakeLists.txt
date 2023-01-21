# FIX: 需要学习下CMake下的Google Test框架

# 查找 GTest 库
find_package(GTest REQUIRED)
# GTest 的头文件
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(test_my_class test_my_class.cpp)

# 链接测试库
target_link_libraries( test_my_class
        ${GTEST_BOTH_LIBRARIES}
        pthread )

# 添加到测试
gtest_discover_tests(test_my_class)
