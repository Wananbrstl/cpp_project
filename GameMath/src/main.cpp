#include "GameMath/Vec3d.h"

#include <iostream>
#include <gtest/gtest.h>


TEST(TEST_VEC3D, test_constructor) {
    EXPECT_EQ(9, 9);
    GameMath::Vec3d zero_vector;
    EXPECT_FLOAT_EQ(zero_vector.x, 0.f);
    EXPECT_FLOAT_EQ(zero_vector.y, 0.f);
    EXPECT_FLOAT_EQ(zero_vector.z, 0.f);

    GameMath::Vec3d v(1, 2, 3);   
    EXPECT_FLOAT_EQ(v.x, 1.f);
    EXPECT_FLOAT_EQ(v.y, 2.f);
    EXPECT_FLOAT_EQ(v.z, 3.f);

    GameMath::Vec3d v_copy(v);
    EXPECT_FLOAT_EQ(v_copy.x, 1.f);
    EXPECT_FLOAT_EQ(v_copy.y, 2.f);
    EXPECT_FLOAT_EQ(v_copy.z, 3.f);
}

TEST(TEST_VEC3D, test_add) {
    GameMath::Vec3d v1(1, 2, 3);
    GameMath::Vec3d v2(2, 3, 1);
    v2 += v1;
    
    EXPECT_FLOAT_EQ(v2.x, 3.f);
    EXPECT_FLOAT_EQ(v2.y, 5.f);
    EXPECT_FLOAT_EQ(v2.z, 4.f);

    GameMath::Vec3d v3 = v1 + v2;
    EXPECT_FLOAT_EQ(v3.x, 4.f);
    EXPECT_FLOAT_EQ(v3.y, 7.f);
    EXPECT_FLOAT_EQ(v3.z, 7.f);
}

TEST(TEST_VEC3D, test_sub) {
    GameMath::Vec3d v1(1.f, 2.f, 3.f);
    GameMath::Vec3d v2(2.f, 4.f, 1.f);
    GameMath::Vec3d v3 = v1 - v2;

    EXPECT_FLOAT_EQ(v3.x, -1.f);
    EXPECT_FLOAT_EQ(v3.y, -2.f);
    EXPECT_FLOAT_EQ(v3.z, 2.f);

}

int main (int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


