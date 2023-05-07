#include "header.h"
#include <cstdio>

#define MyTest 1

#if MyTest
#include <iostream>
#define RED          "/033[0;32;31m"

int test_count = 0;
int passed_test_count = 0;

#define EXPECT_EQ(var1, var2)  \
                do              \
                {                \
                    test_count++;\ 
                    if(var1 == var2) passed_test_count++;\
                    else printf("\033[0;31;40m[error %d-th] error happend at line %d \033[0m\n", test_count - passed_test_count, __LINE__);\
                } while(0)      \

int main (int argc, char *argv[])
{
    EXPECT_EQ(1, sum(0,1));
    EXPECT_EQ(1, sum(-1,1));
    EXPECT_EQ(1, sum(2,1));
    EXPECT_EQ(1, sum(0,1));
        std::cout << "total test case: " << test_count << std::endl;
        std::cout << "passed test case: " << passed_test_count << std::endl;
    std::cout << "passed rate : " << static_cast<float>(passed_test_count) / test_count * 100 << "%" << std::endl;
    return 0;
}
#else
#include <gtest/gtest.h>
TEST(test_sum, normal_number) {
    EXPECT_EQ(1, sum(0, 1));
    EXPECT_EQ(410, sum(1, 409));
    EXPECT_EQ(234, sum(100, 134));
    EXPECT_EQ(20, sum(2, 21));
    EXPECT_EQ(210, sum(200, 10));
}

int main (int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#endif
