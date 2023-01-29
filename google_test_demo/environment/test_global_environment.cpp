#include <gtest/gtest.h>


class TestEnvir : public ::testing::Environment {
public:
    void SetUp() override {
        std::cout << "This is Environment set up" << std::endl;
    }

    void TearDown() override {
        std::cout << "This is Environment tear down" << std::endl;
    }
};


TEST(Suit0, case0) {
    EXPECT_EQ(1, 1);
}
TEST(Suit0, case1) {
    EXPECT_EQ(1, 1);
}
TEST(Suit1, case0) {
    EXPECT_EQ(1, 1);
}
TEST(Suit1, case1) {
    EXPECT_EQ(1, 1);
}

int main (int argc, char *argv[])
{
    testing::AddGlobalTestEnvironment(new TestEnvir);
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
