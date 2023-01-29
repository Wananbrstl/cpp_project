#include <gtest/gtest.h>

class TestCase : public testing::Test {
protected:
    virtual void SetUp(){
        std::cout << "test case begin!" << std::endl;
    }
    virtual void TearDown() {
        std::cout << "test case end!" << std::endl;
    }
};

TEST_F(TestCase, case0) {
    EXPECT_EQ(1,1);
}
TEST_F(TestCase, case1) {
    EXPECT_EQ(1, 1);
}
TEST_F(TestCase, case2) {
    EXPECT_EQ(1, 1);
}
TEST_F(TestCase, case3) {
    EXPECT_EQ(1, 1);
}

int main (int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
