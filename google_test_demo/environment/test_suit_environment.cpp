#include <gtest/gtest.h>

class TestSuit1 : public testing::Test {
public:
    static void SetUpTestSuit() {
        std::cout << "This is Test Suit Set Up" << std::endl;
    }

    static void TearDownTestSuit() {
        std::cout << "This is Test Suit Set Up" << std::endl;
    }
};

TEST_F(TestSuit1, case0) {
    EXPECT_EQ(1,1);
}
TEST_F(TestSuit1, case1) {
    EXPECT_EQ(1, 1);
}
TEST_F(TestSuit1, case2) {
    EXPECT_EQ(1, 1);
}
TEST_F(TestSuit1, case3) {
    EXPECT_EQ(1, 1);
}

int main (int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
