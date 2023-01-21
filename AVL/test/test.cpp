#include <gtest/gtest.h>
#include "AVL.h"


TEST(INSERT_TEST, AVL_TEST) {
    lbn::Node* root = nullptr;
    for(int i = 0; i < 5; ++i)
        root = lbn::insert(root, i);
    EXPECT(root->val, 2);
}

// int main (int argc, char *argv[])
// {
//     return 0;
// }
