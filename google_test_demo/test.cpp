
#include "function.h"
#include <gtest/gtest.h>




namespace lbn{
TEST(DeleteElem, Position) {
    std::vector<int> nums{1, 2, 0, 0, 2};
    std::vector<int> nums_expect{1,2,2,0,2};
    deleteElem(nums, 0);
    for(int i = 0; i < nums.size(); ++i) {
        EXPECT_EQ(nums[i], nums_expect[i]);
    }
}

TEST(DeleteElem, Zero) {
    std::vector<int> nums{0};
    std::vector<int> nums_expect{0};
    deleteElem(nums, 0);
    for(int i = 0; i < nums.size(); ++i) {
        EXPECT_EQ(nums[i], nums_expect[i]);
    }
}

}
