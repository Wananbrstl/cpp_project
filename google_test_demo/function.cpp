#include "function.h"

void deleteElem(std::vector<int> &nums, int elem){
    int left = 0;
    for(int right = 0; right < nums.size(); ++right) {
        if(nums[right] != elem)  {
            nums[left++] = nums[right];
        }
    }
}
