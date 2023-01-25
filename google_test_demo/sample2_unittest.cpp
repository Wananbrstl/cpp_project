#include <vector>
#include <gtest/gtest.h>
#include <iostream>

/*  
    每个测试案例都是独立的
*/
class VectorTest : public testing::Test {
protected:
    void SetUp() override {
        numss.push_back(std::vector<int>());
        numss.push_back(std::vector<int>());
        numss.push_back(std::vector<int>());
    }

    void TearDown() override {
        
    }

    std::vector<std::vector<int>> numss;
};


TEST_F(VectorTest, Constructor) {
    ASSERT_EQ(3, numss.size());
    ASSERT_EQ(0, numss[0].size());
    ASSERT_EQ(0, numss[1].size());
    ASSERT_EQ(0, numss[2].size());
}

TEST_F(VectorTest, Add) {
    for(int i = 0; i < 3; ++i) numss[i].push_back(i);
    for(int i = 0; i < 3; ++i) numss[i].push_back(i);
    for(int i = 0; i < 3; ++ i) EXPECT_EQ(2, numss[i].size());
}

TEST_F(VectorTest, Erase) {
    for(int i = 0; i < 3; ++ i) EXPECT_EQ(0, numss[i].size());
    EXPECT_EQ(3, numss.size());
}
