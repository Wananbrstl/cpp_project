find_package(GTest REQUIRED)

add_executable(test_vec3d test_vec3d.cpp)
target_include_directories(test_vec3d PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(test_vec3d GM GTest::gtest pthread)
add_test(
    NAME test_vec3d 
    COMMAND test_vec3d
    )
