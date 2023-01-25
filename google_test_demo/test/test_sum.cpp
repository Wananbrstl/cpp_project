#include "gtest/gtest.h"
#include <gtest/gtest.h>
#include "sum.h"


TEST(sum_test, tr) {
    EXPECT_EQ(1, sum(1, 0));
    EXPECT_EQ(12111, sum(12000, 111));
    EXPECT_EQ(10, sum(2, 8));
}

TEST(sum_test, f) {
    EXPECT_NE(0, sum(1, 0));
    EXPECT_NE(12110, sum(12000, 111));
    EXPECT_NE(1, sum(-2, 8));
}

TEST_P(test_suite_name, test_name)

