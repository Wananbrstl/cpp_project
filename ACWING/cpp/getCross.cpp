#include<bits/stdc++.h>
#include <cstdio>
#define x first
#define y second

using namespace std;

typedef pair<double, double> Point;
typedef Point Line[2];
typedef Point Vec;

Point operator-(Point a, Point b) {
    return {a.x-b.x, a.y-b.y};
}
Point operator+(Point a, Point b) {
    return {a.x+b.x, a.y+b.y};
}
Point operator*(Point a, double b) {
    return {a.x*b, a.y*b};
}

double cross(Point a, Point b) {
    return a.x*b.y - a.y*b.x;
}
Point getCrossPoint(const Line& a, const Line& b) {
    Vec base = b[1] - b[0];
    double b1 = fabs(cross(base, a[0] - b[0]));
    double b2 = fabs(cross(base, a[1] - b[0]));
    double k = b1 / (b1 + b2);
    // printf("b1 = %lf, b2 = %lf, k = %lf", b1, b2, k);
    return a[0] + (a[1] - a[0]) * k;
}

Line l1,l2;
int main() {
    int n;
    scanf("%d", &n);
    while(n--) {
        scanf("%lf%lf%lf%lf%lf%lf%lf%lf", &l1[0].x, &l1[0].y, &l1[1].x, &l1[1].y, 
                                         &l2[0].x, &l2[0].y, &l2[1].x, &l2[1].y);
        Point pt = getCrossPoint(l1, l2);
        printf("%.10lf %.10lf\n", pt.x, pt.y);
    }
    return 0;
}
