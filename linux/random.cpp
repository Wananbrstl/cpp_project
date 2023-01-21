#include <random>
#include <iostream>

int gcd(int a, int b) {
    return b ? gcd(b, a % b) : a;
}

int main (int argc, char *argv[])
{
    
    std::random_device rd;
    std::mt19937 mt(rd());
    for(int i = 0; i < 10; ++i) {
        std::cout << std::generate_canonical<double, 10>(mt) << "  ";
    }
    std::cout << std::endl;
    std::cout << "gcd(10, 2) = " << gcd(10, 2) << std::endl;
    return 0;
}
