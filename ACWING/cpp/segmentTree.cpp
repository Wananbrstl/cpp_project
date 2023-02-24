#include <bits/stdc++.h>

using namespace std;

class SegmentTree {
private:
    vector<int> nums;

private:
    static int left_child(int idx) {
        return idx * 2;
    }
    static int right_child(int idx) {
        return idx * 2 + 1;
    }
    static int parent(int idx) {
        return idx / 2;
    }
    //TODO: build/query/update/lazy update
    int build(int left, int right) {
        if(left >= right) return nums[left];
        build
    }
public:
    SegmentTree(int n = 10) 
        : nums(n)
    {
        build(0, n-1);
    }
};

int main (int argc, char *argv[])
{
       
    return 0;
}
