#include "gmock/gmock.h"
#include <gtest/gtest.h>
#include <gmock/gmock.h>

class Demo {
public:
    virtual ~Demo() {};
    virtual int get() = 0;
    virtual void set(int) = 0;
private:
    int data_;
};

class MockFoo : public Demo {
public:
    MOCK_METHOD(int, get, ());
    MOCK_METHOD(void, set, (int data));
};

using testing::Return;
TEST(TestSuit, TestCase){
    MockFoo mf;
    EXPECT_CALL(mf, get())
        .Times(1)
        .WillRepeatedly(Return(10));
    EXPECT_EQ(mf.get(), 10);

}

int main (int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
