#include <iostream>


inline int lowbit(int num){
    return num & (- num);
}

int main (int argc, char *argv[])
{
    
    int num = 8;
    std::cout << num - lowbit(num) << std::endl;
    return 0;
}
