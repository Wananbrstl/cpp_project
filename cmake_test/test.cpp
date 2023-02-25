#include <gtest/gtest.h>

TEST(Good, case1) {
    ASSERT_EQ(1, 2);
    EXPECT_EQ(2, 2);
    EXPECT_EQ(2, 2);
    EXPECT_EQ(2, 32);
}

int main (int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
