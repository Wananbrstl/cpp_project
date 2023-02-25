#include <cstdio>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

#define EPS 1e-8
#define N 40040
const double PI = acos(-1);

using namespace std;

struct Point {
    double x, y;
    Point(double xx, double yy) :
        x(xx), y(yy){}
    Point() {
        x = 0.0;
        y = 0.0;
    }

    Point operator-(Point b) const {return Point(x-b.x, y-b.y);}
    Point operator+(Point b) const {return Point(x+b.x, y+b.y);}
    Point operator/(double b) const {return Point(x/b, y/b);}
    Point operator*(double b) const {return Point(x*b, y*b);}
};
int sign(double a) {
    if( fabs(a) < EPS) return 0;
    return a > 0 ? 1 : -1;
}
int dcmp(double a, double b) {
    return sign(a - b);
}
bool cmp(Point a, Point b) {
    return dcmp(a.x, b.x)==0?a.y < b.y:a.x<b.x;
}
double cross(Point a, Point b) {
    return a.x * b.y - a.y * b.x;
}
double dist(Point a, Point b) {
    Point ab = b - a;
    return sqrt(ab.x*ab.x+ab.y*ab.y);
}
int toLeftTest(Point query, Point a, Point b) {
    return sign(cross(b-a, query-a)/2);
}
Point rotate(Point a, double b) {
    return Point(a.x*cos(b)+a.y*sin(b), -a.x*sin(b)+a.y*cos(b));
}

Point pts[N];
int n;
double l, h, r;

double result() {
    sort(pts, pts + n, cmp);
    // for(int i = 0; i < n; ++i) {
    //     printf("(%lf %lf)\n", pts[i].x, pts[i].y);
    // }
    Point q[2 * n];
    int top1 = 0, top2 = 0;
    for(int i = 0; i < n; ++i) {
        while(top1 > 1 && toLeftTest(pts[i], q[top1-2], q[top1-1]) >= 0) top1--; 
        q[top1++] = pts[i];
    }
    top2 = top1;
    for(int i = n - 2; i >= 0; --i) {
        while(top2 > top1 && toLeftTest(pts[i], q[top2-2], q[top2-1]) >= 0) top2--; 
        q[top2++] = pts[i];
    }
    top2 --;
    for(int i = 0; i < top2; ++i){
        printf("%lf %lf\n", q[i].x, q[i].y);
    }
    double res = 0.0;
    for(int i = 0; i < top2; ++i) {
        int fidx = i, sidx = (i + 1) % top2;
        res += dist(q[fidx], q[sidx]);
    }
    return res;
}

int main (int argc, char *argv[])
{
    cin >> n;
    cin >> h >> l >> r;
    int dx[4] = {1, -1, -1, 1};
    int dy[4] = {1, 1, -1, -1};
    h = h / 2 - r;
    l = l / 2 - r;
    double x, y, theta;
    for(int i = 0; i < n; ++i) {
        cin >> x >> y >> theta;
        for(int j = 0; j < 4; ++j) {
            pts[i*4+j] = rotate(Point(dx[j]*l, dy[j]*h), -theta) + Point(x, y);
        }
    }
    n *= 4;
    printf("%.2lf\n", result() + 2 * PI * r);
    return 0;
}
