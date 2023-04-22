// BUG: 有问题 sin函数的最大值
#include <iostream>
#include <cmath>
#include <ctime>

using namespace std;

double rand(double l, double r) {
    return (double)rand() / RAND_MAX * (r - l) + l;
}

double mx = -1e5;

double simulate_annel() {
    srand(time(NULL));
    double cur = rand(-7.0, 7.0);
    for(double T = 7; T > 1e-6; T *= 0.94) {
        double np = rand(fmin(cur - T,-7), fmax(cur + T, 7));
        double dt = np - cur;
        if(exp(-dt / T) > rand(0, 1)) cur = np;
    }
    return cur;
}

int main (int argc, char *argv[])
{

    for(int i = 0; i < 100; ++i) 
        mx = std::max(mx, simulate_annel());

    printf("%lf %lf\n", mx, sin(mx));
    // for(int i = 0; i < 50; ++i) {
    //     printf("%lf\n", rand(0, 1));
    // }
    return 0;
}
