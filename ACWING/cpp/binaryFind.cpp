#include <bits/stdc++.h>

using namespace std;

int findMax(const vector<int>& nums, int left, int right, int tar) {
    if(left > right) return -1;
    int i = left, j = right;
    while(i < j) {
        int mid = (i + j + 1) >> 1;
        if(nums[mid] <= tar) {
            i = mid;
        } else {
            j = mid - 1;
        }
    }
    if(nums[i] == tar)  return i;
    return -1;
}

int findMin(const vector<int>& nums, int left, int right, int tar) {
    if(left > right) return -1;
    int i = left, j = right;
    while(i < j) {
        int mid = (i + j) >> 1;
        if(nums[mid] >= tar) {
            j = mid;
        } else {
            i = mid + 1;
        }
    }
    if(nums[i] == tar)  return i;
    return -1;
}


int main (int argc, char *argv[])
{
    int n, m;
    cin >> n >> m;
    vector<int> nums(n);
    for(int i = 0; i < n; ++i) {
        cin >> nums[i];
    }
    int query;
    for(int i = 0; i < m; ++i){
        cin >> query;
        cout << findMin(nums, 0, n - 1, query) <<  " " 
             << findMax(nums, 0, n - 1, query) << endl;
    }
    return 0;
}
