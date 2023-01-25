#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include <utility>


/* 具有相同的业务逻辑 */

namespace {

// int sum(int a, int b) {return a + b;}

class TestSum : public ::testing::TestWithParam<std::pair<int,int>> {
protected:
    int sum (int a, int b) {
        return a + b;
    }
    int a, b;
};

TEST_P(TestSum, positive) {
    a = GetParam().first;
    b = GetParam().first;
    EXPECT_EQ(a + b, sum(a, b)) << a << "+" << b << "=" << a + b ;
}

INSTANTIATE_TEST_SUITE_P(testsuit, TestSum,
                         ::testing::Values(
                             std::pair<int,int>(1,2), 
                             std::pair<int,int>(3,4),
                             std::pair<int,int>(1,1),
                             std::pair<int,int>(5,4),
                             std::pair<int,int>(1,5)));

} //namespace 
