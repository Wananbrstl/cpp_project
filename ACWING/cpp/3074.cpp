#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <cmath>

#define EPS 1e-12

using namespace std;

double f(double x) {
    return sin(x) / x;
}

double simpson(double l, double r) {
    return (r - l) * ( f(l) + f((l+r)/2)*4 + f(r)) / 6;
}

double asr(double l, double r, double s) {
    double mid = (l + r) / 2;
    double left = simpson(l, mid);
    double right = simpson(mid, r);
    if( fabs(left + right - s) < EPS ) return left + right; 
    return asr(l, mid, left) + asr(mid, r, right);
}

int main (int argc, char *argv[])
{
    double l, r;
    scanf("%lf%lf", &l, &r);
    printf("%lf\n", asr(l, r, simpson(l, r)));
    return 0;
}
